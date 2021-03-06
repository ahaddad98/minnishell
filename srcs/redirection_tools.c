/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:44:55 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/05 16:52:42 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int search_2(char *str)
{
    int i = 0;
    int k = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\\')
        {
            while (str[i] == '\\')
            {
                i++;
                k++;
            }
            if (k % 2 == 0 && (str[i] == '>' || str[i] == '<'))
                return (1);
            else if (k % 2 != 0 && (str[i] == '>' || str[i] == '<'))
                i++;
        }
        if (str[i] == '>' || str[i] == '<' || str[i] == '\'' || str[i] == '\"')
            return (1);
        i++;
    }
    return (0);
}

int count_from(char *line, int i)
{
    int j;

    j = 0;
    if (line[i] == '>' || line[i] == '<')
    {
        while (line[i] != '\0')
            j++;
    }
    return (j);
}

int norm_red(char *line)
{
    int i = 0;
    int k = 0;

    if (line[i] == '\\')
    {
        return (2);
    }
    if (line[i] == '\"' || line[i] == '\'')
        return (1);
    if (line[i] == '>' || line[i] == '<')
        return (3);
    else
        return (0);
}
int count_slach(char *line)
{
    int i;

    i = 0;
    while (line[i] == '\\')
        i++;
    return (i);
}
int count(char *s)
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
            if (s[i] == '>' || s[i] == '<')
            {
                if (k % 2 != 0)
                    return (1);
                else
                    return (0);
            }
        }
        if (s[i] == '\"')
            i = dbl_quote(s, i + 1);
        if (s[i] == '\'')
            i = spl_quote(s, i + 1);
        i++;
    }
    return (0);
}
int kayna2(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    if ((str[i - 1] == '>' || str[i - 1] == '<') && count(str) == 0)
        return (1);

    return (0);
}
char *replace(char *tmp, char *s2)
{
    char *s;

    if (!tmp && !s2)
    {
        return (NULL);
    
    }if (tmp == NULL)
    {
        return(ft_strdup(s2));
    }
    else
    {
        s = tmp;
        tmp = concat_space(s2, tmp);
        // ft_stringdel(&s);
        if(s)
            {
                free(s);
                s = NULL;
            }
    }
    return (tmp);
}

int kayna(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    if ((str[i - 1] == '>' || str[i - 1] == '<') && str[i - 1] != '\\' && str[i - 2] != '\\')
        return (1);
    return (0);
}

int number_red(char *line)
{
    int j;
    int i;
    int k;

    j = 0;
    i = 0;
    k = 0;
    if ((line[i] == '>' && line[i + 1] == '>'))
        j++;
    if ((line[i] == '>' || line[i] == '<'))
        j++;
    while (line[i])
    {

        if (line[i] == '\\')
        {
            k = 0;
            while (line[i] == '\\')
            {
                k++;
                i++;
            }
            if (k % 2 == 0)
            {
                j++;
                i++;
            }
            else
                i++;
        }
        if ((line[i] == '>' && line[i + 1] == '>'))
        {
            i = i + 2;
            j++;
        }
        if ((line[i] == '>' || line[i] == '<') && (line[i - 1] != '\\' && i >= 1))
        {
            j++;
            i++;
        }
        else
        {
            i++;
        }
    }
    return (j);
}
