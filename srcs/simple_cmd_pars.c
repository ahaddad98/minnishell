/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:20:01 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/03 18:46:38 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *sort_all_2(t_list_cmd *lst, t_all *all, char **free_sp, t_path *path)
{
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  while (free_sp[use.i] != NULL)
  {
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
      all = all_conditions(all, free_sp, &use.i);
    else
      condition_3(&use, &free_sp);
  }
  lst->all = update_all(lst->all,use.cmd2, use.arg1, all->red);
  return (lst);
}



int ft_strlen_to_char(char *str)
{
  int i;

  i = 0;
  while (str[i] && str[i] != '>' && str[i] != '<')
  {
    if (str[i] == '\\' || str[i] == '\'' || str[i] == '\"')
      i = index_1(str, i);
    i++;
  }
  return (i);
}
