/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 00:03:18 by zainabdnaya       #+#    #+#             */
/*   Updated: 2021/03/05 17:21:23 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int index_norm1(char *s, int i)
{
    if (s[i] == '\"')
    {
        i = dbl_quote(s, i + 1);
        return (i);
    }
    if (s[i] == '\'')
    {
        i = spl_quote(s, i + 1);
        return (i);
    }
    else
        return (i);
}
int norm_ligne1(char *s, int i, char c, int u)
{
    int z;

    z = 0;
    while (s[i] && (s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
    {
        if (s[i] == '\\')
        {
            u = dbl_quote_norm(s, i);
            i = dbl_quote_norm(s, i) + i;
            if (s[i] == c)
                z = 1;
            if (u % 2 != 0)
                i++;
            else if (u % 2 == 0 && z == 1)
                return (i);
            else if (u % 2 == 0 && z == 0)
                i++;
        }
        i = index_norm1(s, i);
        i++;
    }
    return (i);
}
int ligne1(char *s, char c)
{
    int i;
    int j;
    int u;

    i = 0;
    j = 0;
    u = 0;
    while (s[i])
    {
        while (s[i] && (s[i] == c))
            i++;
        while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
            i++;
        if (s[i] && (s[i] == '\'' || s[i] == '\"' || s[i] == '\\'))
            i = norm_ligne1(s, i, c, u);
        while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\'' && s[i] != '\\')
            i++;
        while (s[i] == c)
            i++;
        j++;
    }
    return (j);
}
int len_each1(const char *s, int i, char c)
{
    int len;

    len = 0;
    while (s[i] && (s[i] == c))
    {
        i++;
        len++;
    }
    return (len);
}

int each_char1(char *s, int i, char c)
{
    int u;
    int z;
    int len;

    z = 0;
    len = len_each1(s, i, c);
    i = len + i;
    while (s[i] && s[i] != c)
    {
        if (s[i] == '\\' && s[i])
        {
            u = dbl_quote_norm(s, i);
            i = dbl_quote_norm(s, i) + i;
            if (s[i] == c)
                z = 1;
            if (u % 2 != 0)
                i++;
            else
                i = each_char_norm(s, i, u, z);
        }
        i = index_norm1(s, i);
        i++;
    }
    return (i - len);
}
char **colomn1(char **array, char *s, char c, int y)
{
    t_use use;

    ft_bzero(&use, sizeof(t_use));
    while (s[use.o] && s[use.o] == c)
        use.o++;
    while (use.w < y)
    {
        use.i = 0;
        if (!(array[use.w] = malloc(sizeof(char) * (each_char1(s, use.o, c) - use.k + 1))))
            free_2d_char(&(array), use.w);
        use.k = each_char1(s, use.o, c);
        while (s[use.o] && use.o < use.k)
        {
            if (s[use.o] && s[use.o] == c && s[use.o - 1] != '\\' && s[use.o - 1] != '\'' && s[use.o - 1] != '\"')
                use.o++;
            array[use.w][use.i++] = s[use.o++];
        }
        array[use.w][use.i] = '\0';
        while (s[use.o] && (s[use.o] == c))
            use.o++;
        use.w++;
    }
    array[use.w] = NULL;
    ft_stringdel(&s);
    return (array);
}

char **ft_minishell_split(const char *line, char c)
{
    char **array;
    char *s;
    int y;

    s = ft_strdup(line);
    y = ligne1(s, c);
    if (!(array = malloc(sizeof(char *) * (y + 1))))
        return (NULL);
    return (colomn1(array, s, c, y));
}