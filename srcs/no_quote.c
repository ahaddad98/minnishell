/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:56:28 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/23 16:31:47 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char witch_quote(char *s)
{
    int i;
    int k;

    i = 0;
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
            else if (k % 2 != 0)
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

char *no_quote(char *s)
{
    int i;
    int j;
    char a;
    char *c;
    char *result;
    char *str;

    i = 0;
    j = 0;
    a = '\0';
    if (s == NULL)
        return (NULL);
    str = strdup(s);
    a = witch_quote(str);
    if (!(result = malloc(sizeof(char) * ft_strlen(str))))
        return (NULL);
    if (we_have_quote(str, a) == 1 /* && exist_equal(str) == 0 */)
    {
        while (str[i])
        {
            if (str[i] == a)
                i++;
            else
                result[j++] = str[i++];
        }
        result[j] = '\0';
    }
    else
        result = strdup(str);
    result = ft_strtrim(result, "\n");
    return (result);
}
int count_slash(char *s, int i)
{
    int j;

    j = 0;
    while (s[i] == '\\' && s[i])
    {
        j++;
        i++;
    }
    return (j);
}

int alloc_slach(char *s, int i)
{
    int j;

    j = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            i = spl_quote(s, i + 1);
        if (s[i] == '\"')
        {
            i = dbl_quote(s, i + 1);
            j = dbl_quote(s, i + 1);
        }
        else
        {
            while (s[i] != '\\' && s[i])
            {
                j++;
                i++;
            }
            if (j != 0)
                return (j);
        }
        i++;
    }
    return (j);
}
char *no_antislach(char *string)
{
    char *str1;
    int i;
    int j;
    int w;
    int u;
    int k;
    char *tmp;
    char *str;
    char *s1;

    str = ft_strdup(string);
    k = 0;
    j = 0;
    i = 0;
    w = 0;
    u = 0;
    if (!(tmp = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (NULL);
    while (str[i] != '\0')
    {
        u = 0;
        w = 0;
        j = 0;
        if (str[i] == 34)
        {
            if (!(str1 = malloc(sizeof(char) * (ft_strlen(str) + 1))))
                return (NULL);
            str1[j++] = str[i++];
            while (str[i] != 34 && str[i])
            {
                if (str[i] == '\\')
                {
                    if (is_valid(str[i + 1]))
                        str1[j++] = str[i++];
                    else
                    {
                        str1[j++] = str[++i];
                        i++;
                    }
                }
                if(str[i] != '\\')
                str1[j++] = str[i++];
            }
            str1[j++] = str[i++];
            str1[j] = '\0';
            // puts("samir");
            // getchar();
            // getchar();
            tmp = join_dolar(tmp, str1);
        }
        if (str[i] == '\\')
        {
            w = count_slash(str, i);
            if (w % 2 != 0)
            {
                i++;
                u = (w - 1) / 2;
                if (!(s1 = malloc(sizeof(char) * (u + 1))))
                    return (NULL);
                i = i + u;
                if (u != 0)
                {
                    while (str[i] == '\\' && str[i])
                        s1[k++] = str[i++];
                    s1[k] = '\0';
                }
            }
            else if (w % 2 == 0)
            {
                u = (w) / 2;
                if (!(s1 = malloc(sizeof(char) * (u + 1))))
                    return (NULL);
                i = i + u;
                while (str[i] == '\\' && str[i])
                    s1[k++] = str[i++];
                s1[k] = '\0';
            }
            tmp = join_dolar(tmp, s1);
        }
        else
        {
            j = 0;
            if (str[i] == '\'')
            {
                u = spl_quote(str, i + 1) + 1;
                if (!(str1 = malloc(sizeof(char) * (u + 1))))
                    return (NULL);
                while (i < u && str[i])
                    str1[j++] = str[i++];
                str1[j] = '\0';
            }
            else
            {
            // puts(&str[i]);
                if (!(str1 = malloc(sizeof(char) * (alloc_slach(str, i) + 1))))
                    return (NULL);
                while (str[i] != '\\' && str[i])
                    str1[j++] = str[i++];
                str1[j] = '\0';
            }
            tmp = join_dolar(tmp, str1);
        }
        // i++;
    }
    return (tmp);
}

// char *no_antislach(char *string)
// {
//     char *str1;
//     int i;
//     int j;
//     int w;
//     int u;
//     int k;
//     char *tmp;
//     char *str;
//     char *s1;

//     str = ft_strdup(string);
//     k = 0;
//     j = 0;
//     i = 0;
//     w = 0;
//     u = 0;
//     if (!(tmp = malloc(sizeof(char) * (ft_strlen(str) + 1))))
//         return (NULL);
//     while (str[i] != '\0')
//     {
//         u = 0;
//         w = 0;
//         j = 0;
//         if (str[i] == '\\')
//         {
//             w = count_slash(str, i);
//             if (w % 2 != 0)
//             {
//                 i++;
//                 u = (w - 1) / 2;
//                 if (!(s1 = malloc(sizeof(char) * (u + 1))))
//                     return (NULL);
//                 i = i + u;
//                 if (u != 0)
//                 {
//                     while (str[i] == '\\' && str[i])
//                         s1[k++] = str[i++];
//                     s1[k] = '\0';
//                 }
//             }
//             else if (w % 2 == 0)
//             {
//                 u = (w) / 2;
//                 if (!(s1 = malloc(sizeof(char) * (u + 1))))
//                     return (NULL);
//                 i = i + u;
//                 while (str[i] == '\\' && str[i])
//                     s1[k++] = str[i++];
//                 s1[k] = '\0';
//             }
//             tmp = join_dolar(tmp, s1);
//         }
//         else
//         {
//             if (str[i] == '\'')
//             {
//                 u = spl_quote(str, i + 1) + 1;
//                 if (!(str1 = malloc(sizeof(char) * (u + 1))))
//                     return (NULL);
//                 while (i < u && str[i])
//                     str1[j++] = str[i++];
//                 str1[j] = '\0';
//             }
//             else
//             {
//                 if (!(str1 = malloc(sizeof(char) * (alloc_slach(str, i) + 1))))
//                     return (NULL);
//                 while (str[i] != '\\' && str[i])
//                     str1[j++] = str[i++];
//                 str1[j] = '\0';
//             }
//             tmp = join_dolar(tmp, str1);
//         }
//     }
//     return (tmp);
// }

int check_antislach(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            i = spl_quote(s, i + 1);
        else if (s[i] == '\\')
            return (1);
        i++;
    }
    return (0);
}

char *slach(char *s)
{
    if (check_antislach(s) == 1)
        return (no_antislach(s));
    else
        return (s);
}
//echo "$PWD\\'kfkf'"