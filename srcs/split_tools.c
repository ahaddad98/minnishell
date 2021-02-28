/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:34:53 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/23 17:08:04 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int dbl_quote(const char *line, int i)
{
    int j;
    int u;

    j = 0;

    // puts(&line[i]);
    while (line[i])
    {
        // puts("heere");
        if (line[i] == '\\')
        {
            u = 0;
            while (line[i] == '\\')
            {
                u++;
                i++;
            }
            if (line[i] == 34)
            {
                if (u % 2 != 0)
                    i++;
                else
                {
                    j = i;
                    break;
                }
            }
        }
        if (line[i] == '\"')
        {
            j = i;
            break;
        }
        i++;
    }
    return (j);
}

int spl_quote(const char *line, int i)
{
    int j;

    j = 0;
    while (line[i])
    {
        // puts(&line[i]);
        if (line[i] == '\'')
        {
            j = i;
            break;
        }
        i++;
    }
    return (j);
}
void *free_array(char **array, int ligne)
{
    ligne = ligne - 1;
    while (ligne > 0)
    {
        free(array[ligne]);
        ligne--;
    }
    free(array);
    return (NULL);
}