/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:20:01 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/26 16:15:01 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"




t_list_cmd *sort_all_2(t_list_cmd *lst, t_all *all, char **free_sp, t_path *path)
{
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  while (free_sp[use.i] != NULL)
  {
    if (condition_1(free_sp, use.i) == 1 || condition_2(free_sp, use.i) == 1)
    {
      all = all_conditions(all, free_sp, &use.i);
    }
    else
    {
      condition_3(&use, &free_sp);
    }
  }
  lst->all = update_all(use.cmd2, use.arg1, all->red);
  return (lst);
}

t_list_cmd *define_each1_01(t_list_cmd *lst, char *string, char *red,
                            t_path *path)
{
  t_all *new1;
  char **tmp;
  char **tmp1;
  int i = 0;
  t_use use;

  ft_bzero(&use, sizeof(t_use));
  if (string == NULL)
  {
    use.cmd = NULL;
    use.arg = NULL;
  }
  else
  {
    // puts(string);
    tmp = shell_space_split(string);
    // while (tmp[i])
    // {
    //   // puts(tmp[i]);
    //   tmp[i] = replace_01(tmp[i], path);
    //   i++;
    // }
    if (ft_strcmp(tmp[0], "echo") == 0 && tmp[1] != NULL && ft_strcmp(tmp[1], "-n") == 0)
    {
      use.cmd = concat_space(tmp[1], tmp[0]);
      use.arg = concat(tmp, 2);
    }
    else
    {
      use.cmd = tmp[0];
      use.arg = concat(tmp, 1);
    }
  }
  new1 = s_cmd_details((use.cmd), (use.arg), red);
  add_all(&lst->all, new1);
  // red = replace_01(red, path);
  lst = redirection_sort(lst, use.cmd, use.arg, red);
  return (lst);
}


int ft_strlen_to_char(char *str)
{
  int i;

  i = 0;
  while (str[i] && str[i] != '>' && str[i] != '<')
  {
    if (str[i] == '\\' || str[i] == '\'' || str[i] == '\"')
      i = index_1(str, i);
    i++;
  }
  return (i);
}

t_list_cmd *redirection_sort(t_list_cmd *lst, char *cmd, char *arg,
                             char *free_sp)
{
  t_use use;
  int k;
  char *tmp;
  char *sign;

  k = 0;
  int j = 0;
  ft_bzero(&use, sizeof(t_use));
  if (free_sp == NULL)
    return (lst);
  // puts(free_sp);
  while (free_sp[use.i])
  {
    tmp = malloc(sizeof(char) * ft_strlen_to_char(&free_sp[use.i]));
    if (free_sp[use.i] == '>' && free_sp[use.i + 1] == '>')
    {
      // puts(&free_sp[use.i]);
      use.sign = malloc(sizeof(char) * 3);
      use.sign[0] = free_sp[use.i];
      use.sign[1] = free_sp[use.i + 1];
      use.sign[2] = '\0';
      use.i = use.i + 1;
    }
    else if (free_sp[use.i] == '>' || free_sp[use.i] == '<')
    {
      use.sign = malloc(sizeof(char) * 2);
      use.sign[0] = free_sp[use.i];
      use.sign[1] = '\0';
      // puts(use.sign);
    }
    else if (free_sp[use.i] != '>' && free_sp[use.i] != '<' && free_sp[use.i] != '\t' && free_sp[use.i] != ' ' && free_sp[use.i] != '\n' && free_sp[use.i])
    {
      k = 0;
      j = 0;
      while (free_sp[use.i] != '\0' && free_sp[use.i] != '>' && free_sp[use.i] != '<' && free_sp[use.i] != '\t' && free_sp[use.i] != ' ' && free_sp[use.i] != '\n')
      {
        if (free_sp[use.i] == '\\' || free_sp[use.i] == '\'' || free_sp[use.i] == '\"')
        {
          j = index_1(free_sp, use.i);
          while (use.i < j)
            tmp[k++] = free_sp[(use.i)++];
        }
        else
          tmp[k++] = free_sp[(use.i)++];
      }
      tmp[k] = '\0';
      use.file_name = ft_strdup(tmp);
      // puts(use.file_name);
      use.red1 = creat_node_r(use.sign, use.file_name);
      add_red(&lst->all->red, use.red1);
      use.i--;
    }
    use.i++;
  }
  // puts(cmd);
  // puts(arg);
  // puts(lst->all-)
  lst->all = update_all(cmd, arg, lst->all->red);
  if (tmp)
    free(tmp);
  if (use.sign)
    free(use.sign);
  if (use.file_name)
    free(use.file_name);
  return (lst);
}