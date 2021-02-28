/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma_or_pipe_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:56:08 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/22 16:52:12 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void part_two(t_list_cmd *lst, t_shell *sh,t_path *path)
{
  char *string;
  char *red;

  // puts(lst->cmd);
  if (search(lst->cmd) == 1)
  {
    string = is_befor_redirection(lst->cmd, sh);
    // puts(string);
    red = is_after_redirection(lst->cmd, sh);
    // puts(red);
    lst = define_each1_01(lst, string, red, path);
  }
  else
    lst = sort_all_1(lst, sh,path);
  // while (lst->all != NULL)
  // {
  //   // printf("************ $$ comma || Pipe $$ *************\n");
  //   printf("cmd : |%s|\n", lst->all->command);
  //   printf("arg : |%s|\n", lst->all->argument);
  //   // printf("red : |%s|\n", lst->all->redirection);

  //   while (lst->all->red != NULL)
  //   {
  //     printf("sign : |%s|\n", lst->all->red->sign);
  //     printf("file_name : |%s|\n", lst->all->red->file_name);
  //     lst->all->red = lst->all->red->next;
  //   }
  //   // printf("/***********************************/\n");
  //   lst->all = lst->all->next;
  // }
}