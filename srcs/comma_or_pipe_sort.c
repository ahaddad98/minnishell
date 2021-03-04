/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma_or_pipe_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:56:08 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/04 09:59:25 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void part_two(t_list_cmd *lst, t_shell *sh, t_path *path)
{
	char *string;
	char *red;

	if (search(lst->cmd) == 1)
	{
		string = is_befor_redirection(lst->cmd, sh);
		red = is_after_redirection(lst->cmd, sh);
		lst = parsing_red(lst, string, red, path);
	}
	else
		lst = spl_cmd(lst, sh, path);
}
