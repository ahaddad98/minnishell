/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:48:56 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/01 15:28:00 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pipe_e(char *line, t_shell *sh)
{
  int i;
  int u;

  i = 0;
  u = 0;
  char c;
  c = quote_char(line, sh);
  while (line[i])
  {
    if (line[i] == '\\')
    {
      u = 0;
      while (line[i] == '\\')
      {
        u++;
        i++;
      }
      if (u % 2 != 0)
        i = i + 1;
      else if (u % 2 == 0)
        continue;
    }
    if (line[i] == '\"')
      i = dbl_quote(line, i + 1);
    if (line[i] == '\'')
      i = spl_quote(line, i + 1);
    if (line[i] == '|')
      return (1);
    i++;
  }
  return (0);
}

t_pipe *both(t_list_cmd *lst, t_shell *sh)
{
  t_pipe *new;
  t_pipe *pipe;
  char **tmp;
  int i;

  if (pipe_e(lst->cmd, sh) == 1)
  {
    tmp = ft_minishell_split(lst->cmd, '|');
    i = 0;
    while (tmp[i] != NULL)
    {
      new = creat_node_p(tmp[i]);
      add_pipe_list(&(pipe), new);
      i++;
    }
    if (tmp)
      free_2d_char(&(tmp), count_line(tmp));
  }
  return (pipe);
}
