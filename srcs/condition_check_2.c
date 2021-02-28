/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:40:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 11:46:38 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int search_norm(char *str, int i, int k, int w)
{
  if (str[i] == '\\')
  {
    while (str[i] == '\\')
    {
      k++;
      i++;
    }
    if (k % 2 == 0 && (str[i] == '>' || str[i] == '<'))
      return (-2);
    else if (k % 2 != 0 && (str[i] == '>' || str[i] == '<'))
    {
      w = 1;
      i++;
    }
    else
      i++;
  }
  if (str[i] == '\'' && (str[i - 1] != '\\' && k % 2 != 0))
    i = spl_quote(str, i + 1);
  if (str[i] == '\"' && (str[i - 1] != '\\' && k % 2 != 0))
    i = dbl_quote(str, i + 1);
  if (w == 1)
    return (-1);
  else
    return (i);
}

int search(char *str)
{
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  if (str[use.i] == '\'' && str[use.i])
    use.i = spl_quote(str, use.i + 1) + 1;
  if (str[use.i] == '\"')
    use.i = dbl_quote(str, use.i + 1) + 1;
  while (str[use.i] != '\0')
  {
    use.i = search_norm(str, use.i, use.k, use.w);
    if (use.i == -1)
      return (0);
    else if (use.i == -2)
      return (1);
    else if (str[use.i] && (str[use.i + 1] != '\0' || str[use.i + 1] != '\n') &&
             (str[use.i] == '>' || str[use.i] == '<' || (str[use.i] == '>' && str[use.i + 1] == '>')))
      return (1);
    else
      use.i++;
  }
  return (0);
}