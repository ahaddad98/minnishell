/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:56:28 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/07 10:56:47 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char witch_quote(char *s, int i)
{
    int k;

    k = 0;
    while (s[i])
    {
        if (s[i] == '\\')
        {
            k = 0;
            while (s[i] == '\\')
            {
                k++;
                i++;
            }
            if (k % 2 == 0 && (s[i] == 39))
                return ('\'');
            else if (k % 2 == 0 && (s[i] == 34))
                return ('\"');
            else /* if (k % 2 != 0) */
                i++;
        }
        if (s[i] == 39)
            return ('\'');
        if (s[i] == 34)
            return ('\"');
        else
            i++;
    }
    return ('\0');
}

int we_have_quote(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int exist_equal(char *str)
{

    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

char *noo_quote(char *s)
{
    int i;
    int j;
    char a;
    char *result;
    char *res;
    char *str;
    i = 0;
    j = 0;
    a = '\0';
    str = ft_strdup(s);
    if (!(result = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (NULL);
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            if (str[i] != 39)
            {
                while (i < spl_quote(str, i))
                    result[j++] = str[i++];
            }
        }
        else if (str[i] == '\"')
        {
            i++;
            if (str[i] != 34)
            {
                while (i < dbl_quote(str, i))
                    result[j++] = str[i++];
            }
        }
        else
            result[j++] = str[i++];
    }
    result[j] = '\0';
    ft_stringdel(&str);
    res = ft_strtrim(result, "\n");
    ft_stringdel(&result);
    return (res);
}

char *no_quote(char *s)
{
    if (witch_quote(s, 0) != '\0')
        return (noo_quote(s));
    else
        return (ft_strdup(s));
}
