/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_before_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:38:53 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/21 17:50:22 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int number_red_1(char *line)
{
  int j;
  int i;

  j = 0;
  i = 0;
  int k;
  k = 0;
  while (line[i])
  {
    if (line[i] == '\\')
    {
      while (line[i] == '\\')
      {
        k++;
        i++;
      }
      if (k % 2 == 0 && (line[i] == '>' || line[i] == '<'))
        j++;
    }
    if (line[i] == '\"')
      i = dbl_quote(line, i + 1) + 1;
    if (line[i] == '\'')
      i = spl_quote(line, i + 1) + 1;
    if ((line[i] == '>' && line[i + 1] == '>'))
    {
      i = i + 2;
      j++;
    }
    if ((line[i] == '>' || line[i] == '<'))
    {
      i++;
      j++;
    }
    else
    {
      i++;
    }
  }
  return (j);
}

int index_1(char *line, int i)
{

  int k;

  k = 0;
  while (line[i])
  {
    if (line[i] == '\\')
    {
      k = 0;
      while (line[i] == '\\' && line[i] != '\0')
      {
        k++;
        i++;
      }
      if (k % 2 != 0)
        return (i + 1);
      else if (k % 2 == 0)
        return (i);
    }
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

char ina_redection(char *s)
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
char *befor(char **cmd)
{
  int j;
  int i;
  char *tmp;
  char **tmp1;
  char *tmp2;
  int o;
  int k;

  j = 0;
  i = 0;
  k = 0;
  o = 0;
  tmp = NULL;
  while (cmd[i] != NULL)
  {
    j = 0;
    tmp1 = NULL;
    if (i == 0 && number_red(cmd[i]) == 0) //|ls \>p|
      tmp = replace(tmp, cmd[i]);
    if (i == 0 && number_red(cmd[i]) > 0 && (cmd[i][0] != '>' && cmd[i][0] != '<')) //l> w echo
    {
      tmp1 = ft_minishell_split(cmd[i], ina_redection(cmd[i]));
      tmp = replace(tmp, tmp1[0]);
    }
    if (condition_1(cmd, i) == 1)
      i = i + 1;
    else if (number_red(cmd[i]) > 0 && (cmd[i][0] != '>' && cmd[i][0] != '<') && i > 0 && kayna(cmd[i - 1]) == 0) //ls <p< o >l && >5> 6>7
    {
      if (cmd[i][j] != '>' && cmd[i][j] != '<')
      {
        tmp1 = ft_minishell_split(cmd[i], ina_redection(cmd[i]));
        tmp = replace(tmp, tmp1[0]);
      }
      if ((cmd[i][j] == '>' || cmd[i][j] == '<') && cmd[i][j])
      {
        while (cmd[i][j] != '\0' && (cmd[i][j] != '\\' || cmd[i][j] != '\'' || cmd[i][j] != '\"'))
          j++;
      }
      while (cmd[i][j] != '\0')
      {
        while (cmd[i][j] && cmd[i][j] != '>' && cmd[i][j] != '<' /* && (cmd[i][j] != '\\' && cmd[i][j] != '\'' && cmd[i][j] != '\"') */)
          j++;
        if ((cmd[i][j] == '>' || cmd[i][j] == '<') && cmd[i][j + 1] == '\0' && cmd[i] != NULL)
          i = i + 1;
        j++;
      }
    }
    else if (number_red(cmd[i]) == 0 && (i >= 1 && kayna(cmd[i - 1]) == 0))
      tmp = replace(tmp, cmd[i]);
    i++;
  }

  return (tmp);
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
  return (tmp);
}
