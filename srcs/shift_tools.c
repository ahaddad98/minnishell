/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:24:15 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/08 15:20:34 by ahaddad          ###   ########.fr       */
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

int			ch_red_dif(t_list_cmd *lst, t_shell *sh)
{
	sh->_red = 0;
	if (ft_strchr(lst->cmd, '>') && ft_strchr(lst->cmd, '<'))
		sh->_red = 1;
	return (sh->_red);
}
