/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:28:12 by ahaddad           #+#    #+#             */
/*   Updated: 2021/03/06 11:50:47 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		check_dup(t_path *path, t_shell *sh, t_all *all, int index)
{
	if (index == 1)
	{
		if (dup2(path->file_desc, 1) < 0)
		{
			ft_putendl_fd(strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
		close(path->file_desc);
		ft_execute1(all, path, sh);
	}
	else if (index == 2)
	{
		if (dup2(path->file_desc, 0) < 0)
		{
			ft_putendl_fd(strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
		close(path->file_desc);
		ft_execute1(all, path, sh);
	}
}

int			che_red_type(t_path *path, t_all *all, int index)
{
	if (!ft_strcmp(">>", all->red->sign))
	{
		path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
				O_APPEND, 0777);
		index = 1;
	}
	else if (!ft_strcmp(all->red->sign, ">"))
	{
		path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
				O_TRUNC, 0777);
		index = 1;
	}
	else if (!ft_strcmp(all->red->sign, "<"))
	{
		if ((path->file_desc = open(all->red->file_name, O_RDONLY)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		else
			index = 2;
	}
	return (index);
}

void		get_multi_red(char **redd, char **anti_red, t_path *path)
{
	while (path->i < (count_line(redd) - 1))
	{
		if ((path->file_desc = open(redd[path->i], O_WRONLY | O_CREAT |
						O_TRUNC, 0777)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		path->i++;
	}
	path->i = 0;
	while (path->i < (count_line(anti_red) - 1))
	{
		if ((path->file_desc = open(redd[path->i], O_RDONLY)) < 0)
			ft_putendl_fd(strerror(errno), 2);
		path->i++;
	}
}

void		get_multi_red2(t_all *all, t_path *path)
{
	path->size = lstsize_2(all->red);
	while (path->size != 1 && path->i < path->size - 1)
	{
		if (ft_strcmp(all->red->sign, ">") || ft_strcmp(all->red->sign, " >>"))
			path->file_desc = open(all->red->file_name, O_WRONLY | O_CREAT |
					O_APPEND, 0777);
		all->red = all->red->next;
		path->i++;
	}
}

void		shift_extra(t_path *path, t_all *all, t_shell *sh)
{
	char		**rd;
	char		**at_rd;

	if_exit_red(all, path);
	if ((path->pid = fork()) == 0)
	{
		if (sh->_red == 1)
		{
			rd = get_reder1(all);
			at_rd = get_antired(all);
			get_multi_red(rd, at_rd, path);
			red_dif(at_rd[count_line(at_rd) - 1], rd[count_line(rd) - 1]);
			ft_execute1(all, path, sh);
			ft_free_2dem_arr((void ***)&rd);
			ft_free_2dem_arr((void ***)&at_rd);
		}
		else
		{
			get_multi_red2(all, path);
			path->index = che_red_type(path, all, path->index);
			check_dup(path, sh, all, path->index);
		}
		exit(0);
	}
	else if (path->pid < 0)
	{
		exit(1);
	}
	wait(0);
}
