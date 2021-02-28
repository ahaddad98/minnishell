/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:24:15 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/28 08:48:45 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			lstsize_2(t_redirection *red)
{
	t_redirection		*list1;
	int					i;

	i = 0;
	list1 = red;
	while (red != NULL)
	{
		i++;
		red = red->next;
	}
	red = list1;
	return (i);
}

void		red_dif(char *f1, char *f2)
{
	int			in;
	int			out;

	in = open(f1, O_RDONLY);
	out = open(f2, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP |
			S_IWGRP | S_IWUSR);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

int			ch_red_dif(t_list_cmd *lst, t_shell *sh)
{
	sh->_red = 0;
	if (ft_strchr(lst->cmd, '>') && ft_strchr(lst->cmd, '<'))
		sh->_red = 1;
	return (sh->_red);
}

char		**get_reder1(t_all *all)
{
	char			**ret;
	t_redirection	*tmp;
	int				i;

	i = -1;
	tmp = all->red;
	while (all->red)
	{
		if (!ft_strcmp(all->red->sign, ">"))
			++i;
		all->red = all->red->next;
	}
	all->red = tmp;
	ret = malloc(sizeof(char *) * (i + 1));
	i = -1;
	tmp = all->red;
	while (all->red)
	{
		if (!ft_strcmp(all->red->sign, ">"))
			ret[++i] = ft_strtrim(all->red->file_name, "\n");
		all->red = all->red->next;
	}
	ret[i] = NULL;
	all->red = tmp;
	return (ret);
}

char		**get_antired(t_all *all)
{
	char			**ret;
	t_redirection	*tmp;
	int				i;

	i = 0;
	tmp = all->red;
	while (all->red)
	{
		if (!ft_strcmp(all->red->sign, "<"))
			i++;
		all->red = all->red->next;
	}
	all->red = tmp;
	ret = malloc(sizeof(char *) * (i + 1));
	i = -1;
	tmp = all->red;
	while (all->red)
	{
		if (!ft_strcmp(all->red->sign, "<"))
			ret[++i] = ft_strtrim(all->red->file_name, "\n");
		all->red = all->red->next;
	}
	ret[i] = NULL;
	all->red = tmp;
	return (ret);
}
