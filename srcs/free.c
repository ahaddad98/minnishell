/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:48:06 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 10:56:22 by ahaddad          ###   ########.fr       */
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