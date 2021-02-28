/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:20:01 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 09:21:14 by zdnaya           ###   ########.fr       */
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
  lst->all = update_all(use.cmd2, use.arg1, all->red);
  return (lst);
}

t_list_cmd *parsing_red(t_list_cmd *lst, char *string, char *red,
                        t_path *path)
{
  t_all *new1;
  char **tmp;
  char **tmp1;
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  if (string == NULL)
  {
    use.cmd = NULL;
    use.arg = NULL;
  }
  else
  {
    tmp = shell_space_split(string);
    use.cmd = tmp[0];
    use.arg = concat(tmp, 1);
    free_array(tmp, count_line(tmp));
  }
  new1 = s_cmd_details((use.cmd), (use.arg), red);
  add_all(&lst->all, new1);
  lst = redirection_sort(lst, &use, red);
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
