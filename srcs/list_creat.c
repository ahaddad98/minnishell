/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_creat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:05:19 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/22 16:41:20 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_all *s_cmd_details(char *s1, char *s2, char *s3)
{
  t_all *all;

  all = malloc(sizeof(t_all));
  // all->command = ft_strtrim(s1, "\n");
  // all->argument = ft_strtrim(s2, "\n");
  all->command = s1;
  all->argument = s2;
  all->redirection = s3;
  all->next = NULL;
  return (all);
}

t_list_cmd *creat_node(char *content)
{
  t_list_cmd *lst;

  lst = malloc(sizeof(t_list_cmd));
  lst->cmd = content;
  lst->next = NULL;
  return (lst);
}

t_redirection *creat_node_r(char *content, char *content1)
{
  t_redirection *red;
  ;
  red = malloc(sizeof(t_redirection));
  red->sign = ft_strtrim(content, "\n");
  red->file_name = ft_strtrim(content1, "\n");
  red->next = NULL;
  return (red);
}
t_pipe *creat_node_p(char *content)
{
  t_pipe *lst;
  lst = malloc(sizeof(t_pipe));
  lst->str_pipe = ft_strtrim(content, "\n");
  lst->next = NULL;
  return (lst);
}
t_all *update_all(char *cmd, char *arg, t_redirection *red)
{
  t_all *new_all;

  new_all = malloc(sizeof(t_all));
  new_all->command = ft_strtrim(cmd, "\n");
  new_all->argument = ft_strtrim(arg, "\n");
  new_all->red = red;
  new_all->next = NULL;
  return (new_all);
}

t_tmp *creat_tmp(char *s1)
{
  t_tmp *tmp;

  tmp = malloc(sizeof(t_tmp));
  tmp->s1 = s1;
  // tmp->s2 = s2;
  tmp->next = NULL;
  return (tmp);
}
