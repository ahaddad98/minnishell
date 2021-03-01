/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:48:06 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/01 22:19:59 by amine            ###   ########.fr       */
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

void    ft_free_2dem_arr(void ***arr)
{
    int i;
    i = 0;
    while ((*arr)[i])
    {
        free((*arr)[i]);
        (*arr)[i] = NULL;
        i++;
    }
    free(*arr);
    *arr = NULL;
}

void    ft_free_arr(void **array)
{
    if (*array)
        free(*array);
    *array = NULL;
}