/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_seperators_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:47:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 11:47:50 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *pars_p_r(t_list_cmd *lst, char *string, char *red, t_path *path)
{
  t_all *new1;
  char **tmp;
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
    use.cmd = ft_strdup(tmp[0]);
    use.arg = concat(tmp, 1);
    new1 = s_cmd_details(use.cmd, use.arg, red);
    free_array(tmp, count_line(tmp));
  }
  add_all(&lst->pipe->all, new1);
  lst = pars_red(lst, red, &use);
  return (lst);
}

t_list_cmd *pars_pipe(t_list_cmd *lst, t_shell *sh, t_path *path)
{
  char **red;
  char *cmd;
  char *arg;
  t_all *new1;

  red = shell_space_split(lst->pipe->str_pipe);
  cmd = red[0];
  arg = concat(red, 1);
  new1 = s_cmd_details1(cmd, arg);
  add_all(&lst->pipe->all, new1);
  free_array(red, count_line(red));
  return (lst);
}
