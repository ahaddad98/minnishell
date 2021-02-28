/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 10:26:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/23 16:35:22 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isalpha2(int c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}

int is_valid(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
        return (1);
    return (0);
}
int until_dollar(char *s, int i)
{
    while (s[i])
    {
        if (s[i] == '\'')
            i = spl_quote(s, i + 1) + 1;
        else if (s[i] == '$' && s[i + 1] == '\\')
            i++;
        else if (s[i] == '\\' && s[i + 1] == '$')
            i++;
        else if (s[i] == '$' && s[i + 1] == '$')
            i++;
        else if (s[i] == '$' && s[i + 1] != '$')
            return (i);
        i++;
    }
    return (i);
}

int in_dollar(char *s, int i)
{
    int j;

    j = 0;
    while (s[i])
    {
        if (s[i] == '$' && s[i])
        {
            while ((s[i] == '$' || ft_isalpha2(s[i]) || ft_isdigit(s[i])) && s[i])
            {
                j++;
                i++;
            }
            return (j);
        }
        i++;
    }
    return (j);
}

int strlen_tmp(t_tmp *tmp)
{
    int i;

    i = 0;
    while (tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    return (i);
}

char *join_dolar(char *s1, char *s2)
{
    char *s3;
    unsigned int len;

    if (!s1 && !s2)
        return (NULL);
    if (!s1 && s2)
        return (s2);
    if (!s2 && s1)
        return (s1);
    len = 0;
    s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (s3 == NULL)
        return (NULL);
    while (*s1)
        s3[len++] = *(s1++);
    while (*s2)
        s3[len++] = *(s2++);
    s3[len] = '\0';
    return (s3);
}

int count_dolars(char *s, int i)
{
    int j;

    j = 0;
    while (s[i] == '$' && s[i])
    {
        j++;
        i++;
    }
    return (j);
}

//  echo "ls \\\\" : syntax error