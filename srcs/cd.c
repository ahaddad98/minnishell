/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:56:11 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 15:06:07 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		cd_cmd_ext(char *nextpath, t_path *path)
{
	char		*s;

	nextpath = ft_strtrim(nextpath, " ");
	if (!nextpath || !ft_strcmp(nextpath, "~"))
	{
		nextpath = get_var_env(path, "$HOME");
		if (chdir(nextpath) < 0)
			ft_putendl_fd(strerror(errno), 1);
		return (1);
	}
	else if (nextpath[0] == '$')
	{
		s = get_var_env(path, nextpath);
		if (!s && (chdir(nextpath) < 0))
			ft_putendl_fd(strerror(errno), 1);
		else
		{
			nextpath = get_var_env(path, nextpath);
			if (chdir(nextpath) < 0)
				ft_putendl_fd(strerror(errno), 1);
		}
		return (1);
	}
	return (0);
}

void			mise_a_jour_env(t_path *path)
{
	int			i;
	char		**spl;
	char		*p;

	i = 0;
	p = getcwd(NULL, 100);
	while (path->env->fullenv[i])
	{
		if (!(spl = ft_split(path->env->fullenv[i], '=')))
			i++;
		else
		{
			if (!ft_strcmp(spl[0], "PWD"))
			{
				path->env->fullenv[i] = ft_strjoin("PWD=", p);
				break ;
			}
			i++;
		}
	}
}

void			cd_cmd(char *nextpath, t_path *path)
{
	nextpath = replace_01(nextpath, path);
	nextpath = no_quote(slach(nextpath));
	if (cd_cmd_ext(nextpath, path) == 1)
	{
		mise_a_jour_env(path);
		return ;
	}
	else if (chdir(nextpath) < 0)
	{
		path->dol_sign = 1;
		ft_putstr_fd(nextpath, 1);
		ft_putendl_fd(strerror(errno), 1);
	}
	else
		path->dol_sign = 0;
	mise_a_jour_env(path);
}
