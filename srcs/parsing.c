/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:39:14 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 10:38:07 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd      *handle_line(t_read *rd, t_list_cmd *lst, t_path *path)
{
  int i;
  t_shell sh;

  i = 0;
  lst = NULL;
  rd->line = ft_strtrim(rd->line, " ");
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
  {
    comand_details(lst, &sh, path);
  // puts("zouhair j3aydani");
  }
  // // // printf("==>%d\n", lstsize_1(lst));
  return (lst);
}