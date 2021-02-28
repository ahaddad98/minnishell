/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epxort_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:11:37 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/27 14:04:24 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ret_check(char *args)
{
	int		i;
	char	**spl;

	spl = ft_split(args, '=');
	if (!ft_var_valid(spl[0][0]))
		return (0);
	else
	{
		i = 1;
		while (spl[0][i])
		{
			if (!ft_true(spl[0][i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int			checkis_valid_var(char *args)
{
	int		i;
	char	**spl;

	if (ft_strchr(args, '='))
		return (ret_check(args));
	else
	{
		if (!ft_var_valid(args[0]))
			return (0);
		else
		{
			i = 1;
			while (args[i])
			{
				if (!ft_true(args[i]))
					return (0);
				i++;
			}
		}
	}
	return (1);
}

char		*get_bef_eq(char *args)
{
	int		i;
	char	*ret;
	int		j;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			break ;
		else
			i++;
	}
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	j = 0;
	while (args[j] && j < i)
	{
		ret[j] = args[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int			is_modif(char *args, int ch_mod, t_path *path)
{
	int		i;
	char	**spl;
	char	*s;

	i = 0;
	spl = ft_split(args, '=');
	while (path->env->fullenv[i])
	{
		s = get_bef_eq(path->env->fullenv[i]);
		if (!ft_strcmp(s, spl[0]))
		{
			ch_mod = i;
			break ;
		}
		i++;
	}
	return (ch_mod);
}
