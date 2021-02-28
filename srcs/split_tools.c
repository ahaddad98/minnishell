/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:34:53 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 10:39:02 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int dbl_quote_norm(const char *line, int i)
{
    int u;

    u = 0;
    while (line[i] == '\\')
    {
        u++;
        i++;
    }
    return (u);
}
int dbl_quote(const char *line, int i)
{
    int j;

    j = 0;
    while (line[i])
    {
        if (line[i] == '\\')
        {
            j = dbl_quote_norm(line, i);
            i = i + j;
            if (line[i] == '\"')
            {
                if (j % 2 != 0)
                    i++;
                else
                    return (i);
            }
        }
        if (line[i] == '\"')
            return (i);
        i++;
    }
    j = 0;
    return (j);
}

int spl_quote(const char *line, int i)
{
    int j;

    j = 0;
    while (line[i])
    {
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