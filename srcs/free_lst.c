/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:59:45 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/03/07 11:10:43 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_all_node(t_all **all)
{
    if ((*all)->command != NULL)
    {
        free((*all)->command);
        (*all)->command = NULL;
    }
    if ((*all)->argument != NULL)
    {
        free((*all)->argument);
        (*all)->argument = NULL;
    }
    free(*all);
    *all = NULL;
}
void free_red(t_redirection **red)
{
    if ((*red)->sign != NULL)
    {
        free((*red)->sign);
        (*red)->sign = NULL;
    }
    if ((*red)->file_name != NULL)
    {
        free((*red)->file_name);
        (*red)->file_name = NULL;
    }
    free(*red);
    *red = NULL;
}

void free_pipe(t_pipe *pipe)
{
    if (pipe->str_pipe != NULL)
        free(pipe->str_pipe);
    if (pipe->all != NULL)
    {
        free_all_node(&pipe->all);
    }
    free(pipe);
    pipe = NULL;
}

void free_lst(t_list_cmd *lst)
{
    t_list_cmd *tmp;
    t_all *all;
    t_redirection *red;
    t_pipe *p;
    while (lst)
    {
        tmp = lst->next;
        if (lst->pipe)
        {
            while (lst->pipe)
            {
                p = lst->pipe->next;
                if (lst->pipe->all->red)
                {
                    while (lst->pipe->all->red)
                    {
                        red = lst->pipe->all->red->next;
                        free_red(&lst->pipe->all->red);
                        lst->pipe->all->red = red;
                    }
                }
                free_pipe(lst->pipe);
                lst->pipe = p;
            }
        }
        if (lst->all)
        {
            while (lst->all)
            {
                all = lst->all->next;
                if (lst->all->red)
                {
                    while (lst->all->red)
                    {
                        red = lst->all->red->next;
                        free_red(&lst->all->red);
                        lst->all->red = red;
                    }
                }
                free_all_node(&lst->all);
                lst->all = all;
            }
        }
        ft_stringdel(&lst->cmd);
        free(lst);
        lst = tmp;
    }
    lst = NULL;
}

void free_dolar(t_tmp **dol)
{
    t_tmp *tmp;

    while (*dol)
    {
        tmp = (*dol)->next;
        if((*dol)->s1)
        {
        free((*dol)->s1);
        (*dol)->s1 = NULL;
        }
        free(*dol);
        *dol = tmp;
    }
    *dol = NULL;
}