/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:48:06 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 12:43:55 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void ft_stringdel(char **string)
{
    free(*string);
    *string = NULL;
}

void    free_1d(char *p)
{
    if (p)
    {
        free(p);
        p = NULL;
    }
}
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
    if ((*all)->red != NULL)
    {
        free((*all)->red->file_name);
        (*all)->red->file_name = NULL;
        free((*all)->red->sign);
        (*all)->red->sign = NULL;
    }
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

void free_all(t_list_cmd *lst, t_shell *sh)
{
    t_list_cmd *tmp;
    t_all *all;
    t_pipe *pipe;
    t_redirection *red;

    while (lst)
    {
        tmp = lst->next;

        // if (lst->pipe != NULL)
        // {
        //     while (lst->pipe)
        //     {

        //         pipe = lst->pipe;
        //         free_pipe(lst->pipe);
        //         lst->pipe = pipe;
        //     }
        // }
        // else
        // {
        while (lst->all)
        {
            all = lst->all;
            free(lst->all);
            // free_all_node(&lst->all);
            lst->all = all;
            // if (search(lst->cmd) == 1)
            // {
            //     while (lst->all->red)
            //     {
            //         red = lst->all->red->next;
            //         free(lst->all->red);
            //         lst->all->red = red;
            //     }
            // }
            // else
            // {
            //     all = lst->all->next;
            //     free(lst->all);
            //     lst->all = all;
            // }
        }
        // }
        // tmp = lst->next;
        // lst = tmp;
        free(lst);
        lst = tmp;
    }
    lst = NULL;
}
