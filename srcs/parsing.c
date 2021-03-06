/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/04 18:31:36 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *__handle_norm(t_read *rd, t_list_cmd *lst, t_path *path)
{
  t_shell sh;

  ft_bzero(&sh, sizeof(t_shell));
  lst = NULL;
  if (check_one(rd->line) == 1)
  {
    sh.simple_cmd = ft_minishell_split(rd->line, '|');
    lst = simple_cmd(lst, sh.simple_cmd);
  }
  else if (check_one(rd->line) == 2)
  {
    sh.simple_cmd = ft_minishell_split(rd->line, ';');
    lst = simple_cmd(lst, sh.simple_cmd);
  }
  else if (check_one(rd->line) == 3)
  {
    sh.simple_cmd = ft_minishell_split(rd->line, ';');
    lst = simple_cmd(lst, sh.simple_cmd);
  }
  comand_details(lst, &sh, path);
  free_2d_char(&sh.simple_cmd, count_line(sh.simple_cmd));
  return (lst);
}

t_list_cmd *handle_line(t_read *rd, t_list_cmd *lst, t_path *path)
{
  t_shell sh;

  ft_bzero(&sh, sizeof(t_shell));
  lst = NULL;
  if (check_one(rd->line) == 0)
  {
    lst = creat_node(rd->line);
    define_each(lst, &sh, path);
    return (lst);
  }
  else
    lst = __handle_norm(rd, lst, path);
  return (lst);
}