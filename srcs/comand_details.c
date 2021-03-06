/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/06 14:17:49 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	comand_details(t_list_cmd *lst, t_shell *sh, t_path *path)
{
	t_list_cmd *lstt;

	lst = link_list(lst, sh);
	lstt = lst;
	while (lst != NULL)
	{
		if (pipe_e(lst->cmd, sh) == 1)
			part_one(lst, sh, path);
		else
		{
			if (pipe_e(lst->cmd, sh) == 1)
				lst = lst->next;
			else
				part_two(lst, sh, path);
		}
		lst = lst->next;
	}
	lst = lstt;
}

void part_two(t_list_cmd *lst, t_shell *sh, t_path *path)
{
	char *string;
	char *red;

	if (search(lst->cmd) == 1)
	{
		string = is_befor_redirection(lst->cmd, sh);
		red = is_after_redirection(lst->cmd, sh);
		lst = parsing_red(lst, string, red, path);
		ft_stringdel(&string);
		ft_stringdel(&red);
	}
	else
		lst = spl_cmd(lst, sh, path);
}

void part_one(t_list_cmd *lst, t_shell *sh, t_path *path)
{
	t_pipe *pipe;
	t_all *all;
	char *string;
	char *str;
	char *arg;
	char *red;
	t_all *new1;

	pipe = lst->pipe;
	while (lst->pipe != NULL)
	{
		if (search(lst->pipe->str_pipe) == 1)
		{
			string = is_befor_redirection(lst->pipe->str_pipe, sh);
			red = is_after_redirection(lst->pipe->str_pipe, sh);
			lst = pars_p_r(lst, string, red, path);
			ft_stringdel(&string);
			ft_stringdel(&red);
		}
		else
			lst = pars_pipe(lst, sh, path);
		lst->pipe = lst->pipe->next;
	}
	lst->pipe = pipe;
}