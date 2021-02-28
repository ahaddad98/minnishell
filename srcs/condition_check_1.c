/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_check_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:59:48 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/11 16:19:11 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_redirection(char *line) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (line[i] != '\0') {
    if (line[i] == '>' )
      j = 1;
    else if (line[i] == '<')
      j = 2;
    else if (line[i] == '>' && line[i + 1] == '>')
      j = 3;
    i++;
  }
  return (j);
}
