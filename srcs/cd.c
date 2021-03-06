/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:56:11 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/06 14:27:14 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		cd_cmd_ext(char *nextpath, t_path *path)
{
	char			*s;

	s = NULL;
	if (!nextpath || !ft_strcmp(nextpath, "~"))
	{
		nextpath = get_var_env(path, "$HOME");
		if (chdir(nextpath) < 0)
			ft_putendl_fd(strerror(errno), 1);
		ft_free_arr((void **)&s);
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
		ft_free_arr((void **)&s);
		return (1);
	}
	return (0);
}

void			update_env(t_path *path)
{
	int				i;
	char			**spl;
	char			*tmp;
	char			*p;

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
				tmp = path->env->fullenv[i];
				path->env->fullenv[i] = ft_strjoin("PWD=", p);
				ft_free_arr((void **)&tmp);
				ft_free_2dem_arr((void ***)&spl);

				break ;
			}
			i++;
		}
		ft_free_2dem_arr((void ***)&spl);
	}
	ft_free_arr((void **)&p);
}

void			cd_cmd(char *nextpath, t_path *path)
{
	if (cd_cmd_ext(nextpath, path) == 1)
	{
		update_env(path);
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
	update_env(path);
}
