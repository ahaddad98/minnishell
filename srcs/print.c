/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:02:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/22 17:00:42 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_all(t_list_cmd *lst, t_shell *sh)
{

  while (lst != NULL)
  {
    if (pipe_e(lst->cmd, sh) == 1) {
      while (lst->pipe) {
        while (lst->pipe->all) {

          // printf("************ $$ PIPE & comma$$ *************\n");
          printf("cmd : |%s|\n", lst->pipe->all->command);
          printf("arg : |%s|\n", lst->pipe->all->argument);
          // printf("red : |%s|\n", lst->pipe->all->redirection);
          while (lst->pipe->all->red != NULL) {
            if (lst->pipe->all->red->sign != NULL)
              printf("sign : |%s|\n", lst->pipe->all->red->sign);
            if (lst->pipe->all->red->file_name != NULL)
              printf("file_name : |%s|\n", lst->pipe->all->red->file_name);
            lst->pipe->all->red = lst->pipe->all->red->next;
          }
          // printf("/***********************************/\n");
          lst->pipe->all = lst->pipe->all->next;
        }
        lst->pipe = lst->pipe->next;
      }
    } else {
    while (lst->all != NULL)
    {
      // printf("************ $$ comma || Pipe $$ *************\n");
      printf("here cmd : |%s|\n", lst->all->command);
      printf("here arg : |%s|\n", lst->all->argument);
      // printf("red : |%s|\n", lst->all->redirection);

      while (lst->all->red != NULL)
      {
        printf("sign : |%s|\n", lst->all->red->sign);
        printf("file_name : |%s|\n", lst->all->red->file_name);
        lst->all->red = lst->all->red->next;
      }
      // printf("/***********************************/\n");
      lst->all = lst->all->next;
      }
    }
    lst = lst->next;
  }
}