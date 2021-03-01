/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_after_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:37:11 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/21 17:48:31 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
char *alloc_red1(char *line)
{

  int i = 0;
  int len;
  char *res;
  int k;

  k = 0;
  res = NULL;
  len = ft_strlen(line);
  while (line[i] != '>' && line[i] != '<' && line[i])
  {
    if (line[i] == '\\')
      i = i + 1;
    if (line[i] == '\"')
      i = dbl_quote(line, i + 1);
    if (line[i] == '\'')
      i = spl_quote(line, i + 1);
    i++;
  }
  if (!(res = malloc(sizeof(char) * (len - i + 1))))
    return (NULL);
  while (line[i] != '\0')
    res[k++] = line[i++];
  res[k] = '\0';
  return (res);
}


char *is_after_redirection(char *s, t_shell *sh)
{
  char *tmp;
  int index;
  int len;
  int len1;
  int len2;
  int start;
  int i;
  int o;
  int k;
  int j;
  char *tmp2;
  char **line;

  o = 0;
  k = 0;
  tmp2 = NULL;
  tmp = NULL;
  line = shell_space_split(s);
  i = 0;
  while (line[i])
  {
    j = 0;
    if (i == 0 && search_2(line[i]) == 0)
      i++;
    else if (condition_1(line, i) == 1 && line[i + 1])
    {
      tmp = replace(tmp, line[i]);
      tmp = replace(tmp, line[i + 1]);
      i = i + 2;
    }
    else if (i >= 1 && kayna2(line[i - 1]) == 0 && search_2(line[i]) == 0 && count(line[i - 1]) == 0)
      i++;
    else
    {
      if (norm_red(line[i]) == 1 || norm_red(line[i]) == 2)
      {
        tmp2 = alloc_red1(line[i]);
        if (!tmp2)
          i++;
        else
        {
          if (norm_red(tmp2) == 3)
          {
            tmp = replace(tmp, tmp2);
            free(tmp2);
          }
          i++;
        }
      }
      else if (check_redirection(line[i]) != 0)
      {
        if ((line[i][0] == '>' || line[i][0] == '<'))
        {
          tmp = replace(tmp, line[i]);
          i++;
        }
        else if ((line[i][0] != '>' || line[i][0] != '<') && i >= 1 && kayna(line[i - 1])) // >1>5> 3>9 echo samir>9>30> 90
        {
          tmp = replace(tmp, line[i]);
          i++;
        }
        else
        {
          tmp = replace(tmp, alloc_red1(line[i]));
          free(alloc_red1(line[i]));
          i++;
        }
      }
      else if (i >= 1 && kayna2(tmp) == 1 && condition_2(line, i) == 0) // khalif dik kayna2 raha mohima >1>5> 3>9 echo samir>9>30> 90
      {
        tmp = replace(tmp, line[i]);
        i++;
      }
    }
  }
  ft_stringdel(line);
  if (!tmp)
    return (NULL);
  else
  {
    tmp = ft_strtrim(tmp, "\n");
  }
  return (tmp);
}