/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 08:49:25 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/04 15:38:32 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		unset_cmd(char *name, t_path *path)
{
	int			i;
	char		**spl;
	char		**args;
	char		**env__p;
	int			j;
	int			k;

	path->check = 0;
	i = -1;
	args = shell_space_split(name);
	while (args[++i])
	{
		j = 0;
		k = 0;
		path->check = 0;
		env__p = malloc(sizeof(char *) * count_line(path->env->fullenv));
		while (j < count_line(path->env->fullenv))
		{
			spl = ft_split(path->env->fullenv[j], '=');
			if (ft_strcmp(spl[0], "_"))
			{
				if (ft_strcmp(spl[0], args[i]))
					env__p[k++] = ft_strdup(path->env->fullenv[j]);
			}
			j++;
			ft_free_2dem_arr((void ***)&spl);
		}
		env__p[k] = NULL;
		ft_free_2dem_arr((void ***)&path->env->fullenv);
		path->env->fullenv = env__p;
	}
	ft_free_2dem_arr((void ***)&args);
}
