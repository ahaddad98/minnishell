/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:34:31 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/06 12:37:23 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *pars_red_norm(t_list_cmd *lst, char *red, t_use *use)
{
  if (red[use->i] == '>' && red[use->i + 1] == '>')
  {
    ft_stringdel(&use->sign);
    use->sign = malloc(sizeof(char) * 3);
    use->sign[0] = red[use->i];
    use->sign[1] = red[use->i + 1];
    use->sign[2] = '\0';
    use->i = use->i + 1;
  }
  else if (red[use->i] == '>' || red[use->i] == '<')
  {
    ft_stringdel(&use->sign);
    use->sign = malloc(sizeof(char) * 2);
    use->sign[0] = red[use->i];
    use->sign[1] = '\0';
  }
  return (use->sign);
}

char *pars_red_norm1(t_list_cmd *lst, char *red, t_use *use, char *tmp)
{
  int k;
  int j;

  k = 0;
  j = 0;
  while (red[use->i] != '\0' && red[use->i] != '>' && red[use->i] != '<' && red[use->i] != '\t' && red[use->i] != ' ' && red[use->i] != '\n')
  {
    if (red[use->i] == '\\' || red[use->i] == '\'' || red[use->i] == '\"')
    {
      j = index_1(red, use->i);
      while (use->i < j)
        tmp[k++] = red[(use->i)++];
    }
    else
      tmp[k++] = red[(use->i)++];
  }
  tmp[k] = '\0';
  return (tmp);
}

t_list_cmd *pars_red(t_list_cmd *lst, char *red, t_use *use)
{
  char *tmp;

  while (red[use->i])
  {
    if (!(tmp = malloc(sizeof(char) * ft_strlen_to_char(&red[use->i]))))
      return (NULL);
    if ((red[use->i] == '>' && red[use->i + 1] == '>') || (red[use->i] == '>' || red[use->i] == '<'))
    {
      use->sign = pars_red_norm(lst, red, use);
    }
    else if (red[use->i] != '>' && red[use->i] != '<' && red[use->i] != '\t' && red[use->i] != ' ' && red[use->i] != '\n' && red[use->i])
    {
      use->file_name = ft_strdup(pars_red_norm1(lst, red, use, tmp));
      add_red(&lst->pipe->all->red, creat_node_r(use->sign, use->file_name));
      ft_stringdel(&use->sign);
      ft_stringdel(&use->file_name);
      use->i--;
    }
    free(tmp);
    use->i++;
  }
  lst->pipe->all = update_all(lst->pipe->all, use->cmd, use->arg, lst->pipe->all->red);
  return (lst);
}

t_list_cmd *redirection_sort(t_list_cmd *lst, t_use *use, char *free_sp)
{
  char *tmp;
  t_redirection *tmp1;

  while (free_sp[use->i])
  {
    tmp = malloc(sizeof(char) * (ft_strlen_to_char(&free_sp[use->i]) + 1));
    if ((free_sp[use->i] == '>' && free_sp[use->i + 1] == '>') || (free_sp[use->i] == '>' || free_sp[use->i] == '<'))
    {
      use->sign = pars_red_norm(lst, free_sp, use);
    }
    else if (free_sp[use->i] != '>' && free_sp[use->i] != '<' && free_sp[use->i] != '\t' && free_sp[use->i] != ' ' && free_sp[use->i] != '\n' && free_sp[use->i])
    {
      use->file_name = ft_strdup(pars_red_norm1(lst, free_sp, use, tmp));
      add_red(&lst->all->red, creat_node_r(use->sign, use->file_name));
      ft_stringdel(&use->sign);
      ft_stringdel(&use->file_name);
      use->i--;
      free(tmp);
      tmp = NULL;
    }
    if(tmp)
    {
    free(tmp);
    tmp = NULL;
    }
    use->i++;
  }
  lst->all = update_all(lst->all, use->cmd, use->arg, lst->all->red);
  return (lst);
}