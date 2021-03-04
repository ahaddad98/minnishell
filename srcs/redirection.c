/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:34:31 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/03 19:06:45 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *pars_red_norm(t_list_cmd *lst, char *red, t_use *use)
{
  if (red[use->i] == '>' && red[use->i + 1] == '>')
  {
    use->sign = malloc(sizeof(char) * 3);
    use->sign[0] = red[use->i];
    use->sign[1] = red[use->i + 1];
    use->sign[2] = '\0';
    use->i = use->i + 1;
  }
  else if (red[use->i] == '>' || red[use->i] == '<')
  {
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
      use->sign = pars_red_norm(lst, red, use);
    else if (red[use->i] != '>' && red[use->i] != '<' && red[use->i] != '\t' && red[use->i] != ' ' && red[use->i] != '\n' && red[use->i])
    {
      use->file_name = ft_strdup(pars_red_norm1(lst, red, use, tmp));
      use->red1 = creat_node_r(use->sign, use->file_name);
      add_red(&lst->pipe->all->red, use->red1);
      use->i--;
    }
    use->i++;
  }
  lst->pipe->all = update_all(lst->pipe->all, use->cmd, use->arg, lst->pipe->all->red);
  // ft_stringdel(&tmp);
  ft_stringdel(&use->sign);
  ft_stringdel(&use->file_name);
  ft_stringdel(&red);
  ft_stringdel(&use->red1->file_name);
  ft_stringdel(&use->red1->sign);
  free(use->red1);

  return (lst);
}

t_list_cmd *redirection_sort(t_list_cmd *lst, t_use *use, char *free_sp)
{
  char *tmp;

  while (free_sp[use->i])
  {
    // puts("here");
    tmp = malloc(sizeof(char) * ft_strlen_to_char(&free_sp[use->i]));
    if ((free_sp[use->i] == '>' && free_sp[use->i + 1] == '>') || (free_sp[use->i] == '>' || free_sp[use->i] == '<'))
      use->sign = pars_red_norm(lst, free_sp, use);
    else if (free_sp[use->i] != '>' && free_sp[use->i] != '<' && free_sp[use->i] != '\t' && free_sp[use->i] != ' ' && free_sp[use->i] != '\n' && free_sp[use->i])
    {
      use->file_name = ft_strdup(pars_red_norm1(lst, free_sp, use, tmp));
      use->red1 = creat_node_r(use->sign, use->file_name);
      add_red(&lst->all->red, use->red1);
      use->i--;
    }
    free(tmp);
    use->i++;
  }
  lst->all = update_all(lst->all, use->cmd, use->arg, lst->all->red);
  // ft_stringdel(&tmp);
  // ft_stringdel(&use->sign);
  // ft_stringdel(&use->file_name);
  // ft_stringdel(&free_sp);
  // ft_stringdel(&use->red1->file_name);
  // ft_stringdel(&use->red1->sign);
  // free(use->red1);
  // puts(lst->all->red->sign);
  // puts(lst->all->red->file_name);

  return (lst);
}