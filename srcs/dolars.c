/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:50:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/23 11:50:33 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int serach_dolar(char *line)
{
    int i;
    int u;

    i = 0;
    u = 0;
    while (line[i])
    {
        // puts("here");
        if (line[i] == '\\') /** \\'p'**/
        {
            u = 0;
            while (line[i] == '\\')
            {
                u++;
                i++;
            }
            if (u % 2 != 0)
                i++;
            else if (u % 2 == 0)
                continue;
        }
        if (line[i] == '\\' && line[i + 1] == '$')
            i = i + 2;
        if (line[i] == '\'')
            i = spl_quote(line, i + 1) + 1;
        if (line[i] == '\"')
        {
            u = dbl_quote(line, i + 1) + 1;
            while (i < u)
            {
                if (line[i] == '$' && line[i + 1] != '\\')
                    return (1);
                i++;
            }
        }
        if (line[i] == '$' && line[i + 1] != '\\')
            return (1);
        i++;
    }
    return (0);
}



char *dolar(char *s, t_path *path)
{
    t_dolar dol;
    // puts(s);
    int i = 0;
    if (!(dol.head = malloc(sizeof(t_tmp))))
        return (NULL);
    ft_bzero(&dol, sizeof(t_dolar));
    while (s[dol.i])
    {
        dol.k = 0;
        dol.w = 0;
        if ((s[dol.i] == '$' && s[dol.i + 1] == '?') || (s[dol.i] == '$' && (s[dol.i + 1] == '\0' || s[dol.i + 1] == '\n')) || (s[dol.i] == '$' && s[dol.i + 1] == '/'))
            dol.res_tmp = case_00(&dol, path, s);
        else if (s[dol.i] == '$' && s[dol.i + 1] != '\\')
        {
            if (!(dol.tmp1 = malloc(sizeof(char) * (in_dollar(s, dol.i) + 1))))
                return (NULL);
            dol.w = count_dolars(s, dol.i);
            if (dol.w % 2 != 0)
                dol.res_tmp = case_01(&dol, s, dol.tmp1, path);
            else
                dol.res_tmp = case_02(&dol, s, dol.tmp1);
            --dol.i;
        }
        else if (s[dol.i] == '\"')
        {
            // puts("here");
            if (!(dol.tmp = malloc(sizeof(char) * (until_dollar(s, dol.i) + 1))))
                return (NULL);
            dol.res_tmp = case_07(&dol, s, dol.tmp,path);
            if (s[dol.i] != '\0')
                --dol.i;
        }
        else if (((s[dol.i] != '$' && s[dol.i] != '\"') || (s[dol.i] == '$' && s[dol.i + 1] == '\\')) && s[dol.i])
        {
            if (!(dol.tmp = malloc(sizeof(char) * (until_dollar(s, dol.i) + 1))))
                return (NULL);
            if (s[dol.i] == '\'')
            {
                dol.res_tmp = case_03(&dol, s, dol.tmp);
                i = 1;
            }
            if ((s[dol.i] == '$' && s[dol.i + 1] == '\\') || s[dol.i] == '\\')
            {
                dol.res_tmp = case_04(&dol, s, dol.tmp);
                i = 1;
            }
            if (s[dol.i] == '$' && s[dol.i + 1] == '$')
            {
                dol.res_tmp = case_05(&dol, s, dol.tmp);
                i = 1;
            }
            if( i != 1)
                dol.res_tmp = case_06(&dol, s, dol.tmp);
            --dol.i;
        }
        i = 0;
        dol.i++;
        add_tmp(&(dol.head), dol.res_tmp);
    }
    while (dol.head != NULL)
    {
        dol.result = join_dolar(dol.result, dol.head->s1);
        dol.head = dol.head->next;
    }
    
    return (dol.result);
}

//  echo $$"$"
//  echo $$$
//  echo "$'"
// "$/"