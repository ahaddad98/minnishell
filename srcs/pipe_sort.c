/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:56:50 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/05 17:55:22 by sqatim           ###   ########.fr       */
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
      ft_stringdel(&string);
      ft_stringdel(&red);
    }
    else
      lst = pars_pipe(lst, sh, path);
    lst->pipe = lst->pipe->next;
  }
  lst->pipe = pipe;
}
