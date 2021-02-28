/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 12:40:02 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
  else if (check_one(rd->line) == 1)
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
  if (check_one(rd->line) != 0)
    comand_details(lst, &sh, path);
  free(sh.simple_cmd);
  sh.simple_cmd = NULL;
  return (lst);
}