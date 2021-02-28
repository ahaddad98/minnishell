/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:40:52 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/21 17:17:24 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int search(char *str)
{
  int i = 0;
  int k = 0;
  int w = 0;

  if (str[i] == '\'' && str[i])
    i = spl_quote(str, i + 1) + 1;
  if (str[i] == '\"')
    i = dbl_quote(str, i + 1) + 1;
  while (str[i] != '\0')
  {
    // puts("hesre");
    if (str[i] == '\\')
    {
      k = 0;
      while (str[i] == '\\')
      {
        // puts("here");
        k++;
        i++;
      }
      if (k % 2 == 0 && (str[i] == '>' || str[i] == '<'))
        return (1);
      else if (k % 2 != 0 && (str[i] == '>' || str[i] == '<'))
      {
        w = 1;
        i++;
      }
      else
        i++;
      // puts(&str[i]);
      // continue;
    }
    if (str[i] == '\'' && (str[i - 1] != '\\' && k % 2 != 0))
      i = spl_quote(str, i + 1);
    if (str[i] == '\"' && (str[i - 1] != '\\' && k % 2 != 0))
      i = dbl_quote(str, i + 1);
    if (str[i] && (str[i] == '>' || str[i] == '<' || (str[i] == '>' && str[i + 1] == '>')) &&
        (str[i + 1] != '\0' || str[i + 1] != '\n'))
      return (1);
    else
      // if (str[i])
      i++;
  }

  if (w == 1)
    return (0);
  return (0);
}

