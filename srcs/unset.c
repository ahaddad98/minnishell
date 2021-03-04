/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 08:49:25 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/04 14:42:13 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		block_tab(t_path *path)
{
	if (!path->check)
		path->env->fullenv[count_line(path->env->fullenv)] = NULL;
	else
		path->env->fullenv[count_line(path->env->fullenv) - 1] = NULL;
}

void		unset_cmd(char *name, t_path *path)
{
	int			i;
	char		**spl;
	char		**args;
	int			j;

	path->check = 0;
	i = -1;
	args = shell_space_split(name);
	while (args[++i])
	{
		j = -1;
		path->check = 0;
		while (++j < count_line(path->env->fullenv))
		{
			spl = ft_split(path->env->fullenv[j], '=');
			if (ft_strcmp(spl[0], "_"))
			{
				if (!ft_strcmp(spl[0], args[i]))
					path->check++;
				if (path->check)
					path->env->fullenv[j] = path->env->fullenv[j + 1];
			}
			ft_free_2dem_arr((void ***)&spl);
		}
		block_tab(path);
	}
	ft_free_2dem_arr((void ***)&args);
}
