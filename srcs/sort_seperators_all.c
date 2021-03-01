/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_seperators_all.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:47:27 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/26 16:14:41 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int ft_strlen_to_char(char *str);

t_list_cmd *define_each1_02(t_list_cmd *lst, char *string, char *red, t_path *path)
{
  t_all *new1;
  char **tmp;
  t_use use;
  int i = 0;

  ft_bzero(&use, sizeof(t_use));
  if (string == NULL)
  {
    use.cmd = NULL;
    use.arg = NULL;
  }
  else
  {
    tmp = shell_space_split(string);
    // while (tmp[i])
    // {
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
      use.cmd = ft_strdup(tmp[0]);
      use.arg = concat(tmp, 1);
    }
    new1 = s_cmd_details(use.cmd, use.arg, red);
  }

  add_all(&lst->pipe->all, new1);
  lst = red_sort_02(lst, use.cmd, use.arg, red, path);
  return (lst);
}

t_list_cmd *red_sort_02(t_list_cmd *lst, char *cmd, char *arg, char *red, t_path *path)
{
  t_use use;
  int k;
  char *tmp;
  char *sign;

  k = 0;
  int j = 0;

  ft_bzero(&use, sizeof(t_use));
  while (red[use.i])
  {
    tmp = malloc(sizeof(char) * ft_strlen_to_char(&red[use.i]));
    if (red[use.i] == '>' && red[use.i + 1] == '>')
    {
      // puts(&red[use.i]);
      use.sign = malloc(sizeof(char) * 3);
      use.sign[0] = red[use.i];
      use.sign[1] = red[use.i + 1];
      use.sign[2] = '\0';
      use.i = use.i + 1;
    }
    else if (red[use.i] == '>' || red[use.i] == '<')
    {
      use.sign = malloc(sizeof(char) * 2);
      use.sign[0] = red[use.i];
      use.sign[1] = '\0';
    }
    else if (red[use.i] != '>' && red[use.i] != '<' && red[use.i] != '\t' && red[use.i] != ' ' && red[use.i] != '\n' && red[use.i])
    {
      k = 0;
      j = 0;
      while (red[use.i] != '\0' && red[use.i] != '>' && red[use.i] != '<' && red[use.i] != '\t' && red[use.i] != ' ' && red[use.i] != '\n')
      {
        if (red[use.i] == '\\' || red[use.i] == '\'' || red[use.i] == '\"')
        {
          j = index_1(red, use.i);
          while (use.i < j)
            tmp[k++] = red[(use.i)++];
        }
        else
          tmp[k++] = red[(use.i)++];
      }
      tmp[k] = '\0';
      use.file_name = ft_strdup(tmp);
      use.red1 = creat_node_r(use.sign, use.file_name);
      add_red(&lst->pipe->all->red, use.red1);
      use.i--;
    }
    use.i++;
  }
  lst->pipe->all = update_all(cmd, arg, lst->pipe->all->red);
  return (lst);
}
t_list_cmd *sort_all_3(t_list_cmd *lst, t_shell *sh, t_path *path)
{
  t_list_cmd *tmp;
  char *string;
  char **red;
  char *cmd;
  char *arg;
  t_all *new1;
  int i = 0;
  red = shell_space_split(lst->pipe->str_pipe);
  // while (red[i])
  // {
  //   red[i] = replace_01(red[i], path);
  //   i++;
  // }
  cmd = red[0];
  if (ft_strcmp(cmd, "echo") == 0 && red[1] != NULL && ft_strcmp(red[1], "-n") == 0)
  {
    cmd = ft_str_join(cmd, " ", red[1]);
    arg = concat(red, 2);
  }
  else
    arg = concat(red, 1);
  new1 = s_cmd_details1(cmd, arg);
  add_all(&lst->pipe->all, new1);
  return (lst);
}
