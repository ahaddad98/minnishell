/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/07 11:26:54 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		comand_details(t_list_cmd *lst, t_shell *sh)
{
	t_list_cmd		*lstt;

	lst = link_list(lst, sh);
	lstt = lst;
	while (lst != NULL)
	{
		if (pipe_e(lst->cmd, sh) == 1)
			part_one(lst);
		else
		{
			if (pipe_e(lst->cmd, sh) == 1)
				lst = lst->next;
			else
				part_two(lst);
		}
		lst = lst->next;
	}
	lst = lstt;
}

void		part_two(t_list_cmd *lst)
{
	char			*string;
	char			*red;

	if (search(lst->cmd) == 1)
	{
		string = is_befor_redirection(lst->cmd);
		red = is_after_redirection(lst->cmd);
		lst = parsing_red(lst, string, red);
		ft_stringdel(&string);
		ft_stringdel(&red);
	}
	else
		lst = spl_cmd(lst);
}

void		part_one(t_list_cmd *lst)
{
	t_pipe			*pipe;
	char			*string;
	char			*red;

	pipe = lst->pipe;
	while (lst->pipe != NULL)
	{
		if (search(lst->pipe->str_pipe) == 1)
		{
			string = is_befor_redirection(lst->pipe->str_pipe);
			red = is_after_redirection(lst->pipe->str_pipe);
			lst = pars_p_r(lst, string, red);
			ft_stringdel(&string);
			ft_stringdel(&red);
		}
		else
			lst = pars_pipe(lst);
		lst->pipe = lst->pipe->next;
	}
	lst->pipe = pipe;
}
