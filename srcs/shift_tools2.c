/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:06:50 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/05 15:08:35 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		if_exit_red(t_all *all, t_path *path)
{
	path->index = 0;
	path->i = 0;
	if (ft_strcmp(all->command, "exit") == 0)
	{
		ft_putendl_fd(all->command, 1);
		if (!ft_strncmp(">>", all->red->sign, 2))
			path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_APPEND, 0777);
		else if (!ft_strncmp(all->red->sign, ">", 1))
			path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_TRUNC, 0777);
		exit(0);
	}
}
