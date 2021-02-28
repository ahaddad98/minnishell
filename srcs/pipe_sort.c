/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:56:50 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/27 12:18:16 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void part_one(t_list_cmd *lst, t_shell *sh, t_path *path)
{
  t_pipe *pipe;
  t_all *all;
  char *string;
  char *str;
  char **tmp;
  char *cmd;
  char *arg;
  char *red;
  t_all *new1;

  pipe = lst->pipe;
  while (lst->pipe != NULL)
  {
    if (search(lst->pipe->str_pipe) == 1)
    {
      string = is_befor_redirection(lst->pipe->str_pipe, sh);
      red = is_after_redirection(lst->pipe->str_pipe, sh);
      lst = pars_p_r(lst, string, red, path);
    }
    else
      lst = pars_pipe(lst, sh, path);
    lst->pipe = lst->pipe->next;
  }
  lst->pipe = pipe;
}
