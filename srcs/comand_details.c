/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_details.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:00:25 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/04 09:59:04 by zdnaya           ###   ########.fr       */
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
