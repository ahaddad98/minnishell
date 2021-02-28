/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_before_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:19:38 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/27 18:46:03 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int norm_index1(char *line, int i)
{
  int k;
  int z;

  k = 0;
  z = 0;
  while (line[i] == '\\' && line[i] != '\0')
  {
    k++;
    i++;
  }
  if (k % 2 != 0)
    z = i + 1;
  else if (k % 2 == 0)
    z = i;
  return (z);
}

int index_1(char *line, int i)
{
  while (line[i])
  {
    if (line[i] == '\\')
      i = norm_index1(line, i);
    if (line[i] == '\"')
    {
      i = dbl_quote(line, i + 1) + 1;
      return (i);
    }
    if (line[i] == '\'')
    {
      i = spl_quote(line, i + 1) + 1;
      return (i);
    }
    i++;
  }
  return (i);
}

char witch_red(char *s)
{
  int i;

  i = 0;
  while (s[i])
  {
    if ((s[i] == '\\' || s[i] == '\'' || s[i] == '\"'))
      i = index_1(s, i);
    if (s[i] == '>')
      return ('>');
    if (s[i] == '<')
      return ('<');
    i++;
  }
  return (0);
}

char *is_befor_redirection(char *line, t_shell *sh)
{
  char *tmp;
  char **cmd;

  cmd = shell_space_split(line);
  tmp = befor(cmd);
  if (!tmp)
    return (NULL);
  else
    tmp = ft_strtrim(tmp, "\n");
  free_array(cmd, count_line(cmd));
  return (tmp);
}
