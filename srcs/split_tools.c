/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zainabdnayagmail.com <zainabdnayagmail.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:34:53 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/01 09:44:41 by zainabdnaya      ###   ########.fr       */
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