/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 00:03:18 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/02/24 14:36:32 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int norm_ligne1(char *s, int i, char c)
{
    int u;
    int z;

    u = 0;
    z = 0;
    while (s[i] && (s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
    {
        if (s[i] == '\\' && s[i]) /** \\'p'**/
        {
            u = 0;
            while (s[i] == '\\')
            {
                u++;
                i++;
            }
            if (s[i] == 'c')
            {
                if (u % 2 != 0)
                    i++;
                else if (u % 2 == 0)
                    continue;
            }
            else
            {
                if (u % 2 != 0)
                {
                    i++;
                    z = 1;
                }
                else
                    z = 1;
            }
        }
        if (s[i] == '\"' && z == 0)
            i = dbl_quote(s, i + 1);
        if (s[i] == '\'' && z == 0)
            i = spl_quote(s, i + 1);
        i++;
    }
    // while (s[i] &&  s[i] != 'c')
    //     i++;
    return (i);
}
int ligne1(char *s, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[i])
    {
        while (s[i] && (s[i] == c))
            i++;
        while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
            i++;
        if (s[i] && (s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
        {
            i = norm_ligne1(s, i, c);
            // puts(&s[i]);
        }
        while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
            i++;

        while ((s[i] == c) && s[i])
            i++;
        j++;
    }
    return (j);
}

int each_char1(char *s, int i, char c)
{
    int len;
    int u;
    int z;

    len = 0;
    u = 0;
    z = 0;
    while (s[i] && (s[i] == c))
    {
        i++;
        len++;
    }
    while (s[i] && s[i] != c)
    {
        if (s[i] == '\\' && s[i]) /** \\'p'**/
        {
            u = 0;
            while (s[i] == '\\')
            {
                u++;
                i++;
            }
            if (s[i] == 'c')
            {
                if (u % 2 != 0)
                    i++;
                else if (u % 2 == 0)
                    continue;
            }
            else
            {
                if (u % 2 != 0)
                {
                    i++;
                    z = 1;
                }
                else
                    z = 1;
            }
        }
        if (s[i] == '\"' && z == 0)
        {
            i = dbl_quote(s, i + 1);
        }
        if (s[i] == '\'' && z == 0)
            i = spl_quote(s, i + 1);
        i++;
    }
    return (i - len);
}
char **colomn1(char **array, char *s, char c, int y)
{
    int o;
    int i;
    int k;
    int w;

    i = 0;
    o = 0;
    k = 0;
    w = 0;
    while (s[o] && s[o] == c)
        o++;
    while (w < y)
    {
        i = 0;
        if (!(array[w] = malloc(sizeof(char) * (each_char1(s, o, c) - k + 1))))
            free_array(array, w);
        k = each_char1(s, o, c);
        while (s[o] && o < k)
        {
            if (s[o] && s[o] == c && s[o - 1] != '\\' && s[o - 1] != '\'' && s[o - 1] != '\"')
                o++;
            array[w][i++] = s[o++];
        }
        array[w][i] = '\0';
        while (s[o] && (s[o] == c))
            o++;
        w++;
    }
    array[w] = NULL;
    return (array);
}

char **ft_minishell_split(const char *line, char c)
{
    char **array;
    char *s;
    int y;

    s = strdup(line);
    y = ligne1(s, c);
    if (!(array = malloc(sizeof(char *) * (y + 1))))
        return (NULL);
    return (colomn1(array, s, c, y));
}