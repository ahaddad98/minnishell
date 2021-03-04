/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:59:45 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/03/03 18:52:19 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_all_node(t_all **all)
{
    t_redirection *red;
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
    // if ((*all)->red != NULL)
    // {
    //     // if ((*all)->red == NULL)
    //         // puts("shi kharya");
    //     while ((*all)->red)
    //     {
    //         // puts("hamza l kelb");
    //         red = (*all)->red->next;
    //         free((*all)->red->file_name);
    //         (*all)->red->file_name = NULL;
    //         free((*all)->red->sign);
    //         (*all)->red->sign = NULL;
    //         (*all)->red = red;
    //     }
        // free((*all)->red);
    // }
    free(*all);
    *all = NULL;
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

    while (lst)
    {
        tmp = lst->next;
        if (lst->pipe)
            free_pipe(lst->pipe);
        if (lst->all)
        {
            while (lst->all)
            {
                // puts("zainab bagra");
                all = lst->all->next;
                free_all_node(&lst->all);
                lst->all = all;
            }
        }
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
        free((*dol)->s1);
        (*dol)->s1 = NULL;
        free(*dol);
        *dol = tmp;
    }
    *dol = NULL;
}