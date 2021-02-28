/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:27:51 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/22 17:43:11 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int norm_ligne(const char *s, int i)
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
            if (s[i] == ' ' || s[i] == '\t')
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
            // puts(&s[i]);
        }
        if (s[i] == '\'' && z == 0)
            i = spl_quote(s, i + 1);
        i++;
        while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
            i++;
    }
    return (i);
}
int ligne(const char *s)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[i])
    {
        while (s[i] && (s[i] == ' ' || s[i] == '\t'))
            i++;
        while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
            i++;
        if (s[i] && (s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
            i = norm_ligne(s, i) + 1;
        while ((s[i] == ' ' || s[i] == '\t') && s[i])
            i++;
        j++;
    }
    return (j);
}

int each_char(const char *s, int i)
{
    int len;
    int u;
    int z;

    len = 0;
    u = 0;
    z = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
    {
        i++;
        len++;
    }
    while (s[i] && s[i] != ' ' && s[i] != '\t')
    {
        if (s[i] == '\\') /** \\'p'**/
        {
            u = 0;
            while (s[i] == '\\')
            {
                u++;
                i++;
            }
            if (s[i] == ' ' || s[i] == '\t')
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
    return (i - len);
}
char **colomn(char **array, const char *s, int y, int w)
{
    int o;
    int i;
    int k;

    i = 0;
    o = 0;
    k = 0;
    while (s[o] && (s[o] == ' ' || s[o] == '\t'))
        o++;
    while (w < y)
    {
        i = 0;
        if (!(array[w] = malloc(sizeof(char) * (each_char(s, o) - k + 1))))
            free_array(array, w);
        k = each_char(s, o);
        while (s[o] && o < k)
            array[w][i++] = s[o++];
        array[w][i] = '\0';
        while (s[o] && (s[o] == ' ' || s[o] == '\t'))
            o++;
        w++;
    }
    array[w] = NULL;
    return (array);
}

char **shell_space_split(const char *line)
{
    char **array;
    int y;
    int w;

    w = 0;
    y = 0;

    y = ligne(line);
    // printf("==>%d\n", y);
    if (!(array = malloc(sizeof(char *) * (y + 1))))
        return (NULL);
    return (colomn(array, line, y, w));
}