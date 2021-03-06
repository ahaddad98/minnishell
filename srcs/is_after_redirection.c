/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_after_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:41:55 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/05 17:49:14 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *alloc_red1(char *line, int i)
{
  char *res;
  int k;

  k = 0;
  i = 0;
  res = NULL;
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
  if (!(res = malloc(sizeof(char) * ((ft_strlen(line)) - i + 1))))
    return (NULL);
  while (line[i] != '\0')
    res[k++] = line[i++];
  res[k] = '\0';
  return (res);
}

char *after_norm(char **line, char *tmp, char *tmp2, t_use *use)
{
  tmp2 = alloc_red1(line[use->i], use->o);
  if (!tmp2)
    use->i++;
  else
  {
    if (norm_red(tmp2) == 3)
    {
      // puts("1");
      tmp = replace(tmp, tmp2);
    }
    use->i++;
  }
  if (tmp2)
  {
    free(tmp2);
    tmp2 = NULL;
  }
  return (tmp);
}

char *after_norm1(char **line, char *tmp, t_use *use)
{
  char *tmp1;

  if ((line[use->i][0] == '>' || line[use->i][0] == '<'))
  {
    // tmp1 = tmp;
    tmp = replace(tmp, line[use->i]);
    //  puts("dkk");
    // ft_stringdel(&tmp1);
    use->i++;
  }
  else if ((line[use->i][0] != '>' || line[use->i][0] != '<') && use->i >= 1 && kayna(line[use->i - 1]))
  {
    // tmp1 = tmp;
    tmp = replace(tmp, line[use->i]);
    // ft_stringdel(&tmp1);
    use->i++;
  }
  else
  {
    tmp1 = alloc_red1(line[use->i], use->o);
    tmp = replace(tmp, tmp1);
    free(tmp1);
    tmp1 = NULL;
    // free(alloc_red1(line[use->i], use->o));
    // ft_stringdel(&tmp1);
    use->i++;
  }
  return (tmp);
}

int condition_if(char **line, t_use use)
{
  if (use.i == 0 && search_2(line[use.i]) == 0)
    return (1);
  else if (condition_1(line, use.i) == 1 && line[use.i + 1])
    return (1);
  else if (use.i >= 1 && kayna2(line[use.i - 1]) == 0 && search_2(line[use.i]) == 0 && count(line[use.i - 1]) == 0)
    return (1);
  else
    return (0);
}

char *norm_first(char **line, t_use *use, char *tmp)
{
  char *tmp1;

  if (use->i == 0 && search_2(line[use->i]) == 0)
    use->i++;
  else if (condition_1(line, use->i) == 1 && line[use->i + 1])
  {
    // tmp1 = tmp;
    tmp = replace(tmp, line[use->i]);
    // ft_stringdel(&tmp1);
    // tmp1 = tmp;
    tmp = replace(tmp, line[use->i + 1]);
    // ft_stringdel(&tmp1);
    use->i = use->i + 2;
  }
  else if (use->i >= 1 && kayna2(line[use->i - 1]) == 0 && search_2(line[use->i]) == 0 && count(line[use->i - 1]) == 0)
    use->i++;
  return (tmp);
}

char *last_norm(char **line, t_use *use, char *tmp, char *tmp2)
{
  char *tmp1;
  if ((norm_red(line[use->i]) == 1 || norm_red(line[use->i]) == 2))
    tmp = after_norm(line, tmp, tmp2, use);
  else if (check_redirection(line[use->i]) != 0)
  {
    // tmp1 = tmp;
    tmp = after_norm1(line, tmp, use);
    // ft_stringdel(&tmp1);
  }
  else if (use->i >= 1 && kayna2(tmp) == 1 && condition_2(line, use->i) == 0)
  {
    tmp = replace(tmp, line[use->i]);
    use->i++;
  }
  free(tmp2);
  tmp2 = NULL;
  return (tmp);
}

char *is_after_redirection(char *s, t_shell *sh)
{
  char *tmp;
  t_use use;
  char *tmp2;
  char **line;
  char *one;

  tmp2 = NULL;
  tmp = NULL;
  line = shell_space_split(s);
  ft_bzero(&use, sizeof(t_use));

  tmp = malloc(sizeof(char) * (ft_strlen(s)));
  while (line[use.i])
  {
    // one = tmp;
    if (condition_if(line, use) == 1)
    {
      // one = tmp;
      tmp = norm_first(line, &use, tmp);
      // ft_stringdel(&one);
    }
    else
    {
      // one = tmp;
      tmp = last_norm(line, &use, tmp, tmp2);
      // ft_stringdel(&one);
    }
  }
  free_2d_char(&(line), count_line(line));
  return (tmp);
}