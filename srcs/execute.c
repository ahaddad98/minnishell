/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:04:15 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/28 14:30:21 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int					is_slash(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void				exe(char *p1, char *cmd, char **tmp1, t_path *path)
{
	int				status;
	int				a;

	status = 0;
	a = fork();
	if (!a)
	{
		if (p1 && cmd[0] != '\n' && tmp1[0])
			if (execve(p1, tmp1, path->env->fullenv) == -1)
			{
				ft_putstr_fd("bash: ", 1);
				ft_putstr_fd(p1, 1);
				ft_putendl_fd(": commande not found99", 1);
			}
		exit(0);
	}
	wait(&status);
	if (WEXITSTATUS(status))
		path->dol_sign = WEXITSTATUS(status);
	else
		path->dol_sign = 0;
}

char				*ft_get_cmd(char *p1, char *p, char **tmp1, t_path *path)
{
	if (is_slash(tmp1[0]) == 1)
	{
		p1 = ft_strdup(tmp1[0]);
		path->d = 1;
	}
	else if (path->i == 0 && !p)
	{
		p1 = getcwd(NULL, 100);
		p1 = ft_strjoin(p1, "/");
		p1 = ft_strjoin(p1, tmp1[0]);
		path->d = 1;
	}
	else if (!path->d)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(tmp1[0], 1);
		ft_putendl_fd(": commande not found", 1);
		path->dol_sign = 127;
	}
	return (p1);
}

char				*cmd_slash(char **tmp, char *p1, t_path *path, char **tmp1)
{
	struct stat		buffer;

	path->i = -1;
	while (tmp[++path->i])
	{
		tmp[path->i] = ft_strjoin(tmp[path->i], "/");
		tmp[path->i] = ft_strjoin(tmp[path->i], tmp1[0]);
		if (lstat(tmp[path->i], &buffer) == 0)
		{
			p1 = ft_strdup(tmp[path->i]);
			path->d = 1;
			break ;
		}
	}
	return (p1);
}

void				exeute(t_path *path, char *cmd)
{
	char			**tmp;
	char			**tmp1;
	char			*p;
	char			*p1;

	path->i = -1;
	p1 = NULL;
	tmp1 = shell_space_split(cmd);
	p = get_var_env(path, "$PATH");
	if (tmp1[0])
	{
		if (p)
		{
			tmp = ft_split(p, ':');
			p1 = cmd_slash(tmp, p1, path, tmp1);
		}
		p1 = ft_get_cmd(p1, p, tmp1, path);
		if (!p1)
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(tmp1[0], 1);
			ft_putendl_fd(": commande not found", 1);
			path->dol_sign = 127;
		}
		if (path->d)
			exe(p1, cmd, tmp1, path);
	}
}
