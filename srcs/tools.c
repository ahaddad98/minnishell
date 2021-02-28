/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 10:57:49 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/28 11:00:39 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*ft_str_in_str(const char *s1, const char *s2)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (!s2[j])
		return ((char *)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			j = 1;
			while (s2[j] && s2[j] == s1[i + j])
				j++;
			if (!s2[j] && !s1[i + j])
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (NULL);
}

int				ft_2strlen(char **str)
{
	int			i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int				count_line(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

static void		*leak(char **spl, int j)
{
	j = j - 1;
	while (spl[j])
	{
		free(spl[j]);
		j--;
	}
	free(spl);
	return (NULL);
}
