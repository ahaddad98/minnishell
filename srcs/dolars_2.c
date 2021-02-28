/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:24:29 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/21 17:46:42 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tmp *case_00(t_dolar *dol, t_path *path, char *s)
{
    if ((s[dol->i] == '$' && s[dol->i + 1] == '?'))
    {
        dol->two = ft_itoa(path->dol_sign);
        dol->c1 = creat_tmp(dol->two);
    }
    if (s[dol->i] == '$' && (s[dol->i + 1] == '\0' || s[dol->i + 1] == '\n'))
        dol->c1 = creat_tmp(ft_strdup("$"));
    if (s[dol->i] == '$' && s[dol->i + 1] == '/')
        dol->c1 = creat_tmp(ft_strdup("$/"));

    dol->i++;
    return (dol->c1);
}
t_tmp *case_01(t_dolar *dol, char *s, char *tmp1, t_path *path)
{
    dol->i++;
    dol->u = (dol->w - 1) / 2;
    if (!(dol->s1 = malloc(sizeof(char) * (dol->u + 1))))
        return (NULL);
    dol->i = dol->i + dol->u;
    if (dol->u != 0)
    {
        while (s[dol->i] == '$' && s[dol->i])
            dol->s1[dol->k++] = s[dol->i++];
        dol->s1[dol->k] = '\0';
    }
    dol->k = 0;
    if ((ft_isalpha2(s[dol->i]) == 1 || ft_isdigit(s[dol->i]) == 1 || s[dol->i] == '_') && s[dol->i])
    {
        while ((ft_isalpha2(s[dol->i]) == 1 || ft_isdigit(s[dol->i]) == 1 || s[dol->i] == '_') && s[dol->i])
            tmp1[dol->k++] = s[dol->i++];
        tmp1[dol->k] = '\0';
        dol->var_tmp = search_env(path->env->fullenv, tmp1);
        dol->var_tmp = join_dolar(dol->s1, dol->var_tmp);
        dol->c1 = creat_tmp(dol->var_tmp);
    }
    else
    {
        tmp1 = NULL;
        dol->var_tmp = join_dolar(dol->s1, NULL);
        dol->c1 = creat_tmp(dol->var_tmp);
    }
    return (dol->c1);
}
t_tmp *case_02(t_dolar *dol, char *s, char *tmp1)
{
    dol->u = (dol->w) / 2;
    dol->i = dol->i + dol->u;
    if (!(dol->s1 = malloc(sizeof(char) * (dol->u + 1))))
        return (NULL);
    while (s[dol->i] == '$' && s[dol->i])
    {
        dol->s1[dol->k++] = '$';
        dol->i++;
    }
    dol->s1[dol->k] = '\0';
    dol->k = 0;
    while ((s[dol->i] != '$' || (s[dol->i] == '$' && s[dol->i + 1] == '\"')) && s[dol->i])
        tmp1[dol->k++] = s[dol->i++];
    tmp1[dol->k] = '\0';
    dol->c1 = creat_tmp(join_dolar(dol->s1, tmp1));
    return (dol->c1);
}
t_tmp *case_03(t_dolar *dol, char *s, char *tmp)
{
    dol->k = 0;
    dol->j = spl_quote(s, dol->i + 1) + dol->i;
    while (dol->i < dol->j && s[dol->i])
        tmp[dol->k++] = s[dol->i++];
    tmp[dol->k] = '\0';
    dol->c1 = creat_tmp(tmp);
    return (dol->c1);
}
t_tmp *case_04(t_dolar *dol, char *s, char *tmp)
{
    dol->w = 0;
    dol->k = 0;
    if (s[dol->i] == '$' && s[dol->i + 1] == '\\')
        tmp[dol->k++] = s[dol->i++];
    if (s[dol->i] == '\\')
    {
        while (s[dol->i] == '\\' && s[dol->i])
        {
            tmp[dol->k++] = s[dol->i++];
            dol->w++;
        }
        if (dol->w % 2 == 0)
        {
            if (s[dol->i] == '$')
                dol->c1 = creat_tmp(tmp);
            else
            {
                while ((s[dol->i] != '$' && s[dol->i] != '\"' && s[dol->i] != '\'') && s[dol->i])
                    tmp[dol->k++] = s[dol->i++];
                tmp[dol->k] = '\0';
                dol->c1 = creat_tmp(tmp);
            }
        }
        else
        {
            tmp[dol->k++] = s[dol->i++];
            tmp[dol->k] = '\0';
            dol->c1 = creat_tmp(tmp);
        }
    }
    if (dol->u == 0)
    {
        dol->m = (dol->u - 1) / 2;
        while (dol->i < dol->i + dol->m)
        {
            {
                tmp[dol->k++] = '$';
                dol->i++;
            }
        }
        tmp[dol->k] = '\0';
        dol->c1 = creat_tmp(tmp);
    }
    else
    {
        while (s[dol->i] != '$' && s[dol->i])
            tmp[dol->k++] = s[dol->i++];
        tmp[dol->k] = '\0';
        dol->c1 = creat_tmp(tmp);
    }
    return (dol->c1);
}

t_tmp *case_05(t_dolar *dol, char *s, char *tmp)
{
    while (s[dol->i] == '$' && s[dol->i + 1] == '$')
        tmp[dol->k++] = s[dol->i++];
    tmp[dol->k] = '\0';
    dol->c1 = creat_tmp(tmp);
    return (dol->c1);
}

t_tmp *case_06(t_dolar *dol, char *s, char *tmp)
{
    while ((s[dol->i] != '$' || (s[dol->i] == '$' && s[dol->i + 1] == '\"')) && s[dol->i])
        tmp[dol->k++] = s[dol->i++];
    tmp[dol->k] = '\0';
    dol->c1 = creat_tmp(tmp);
    return (dol->c1);
}

t_tmp *case_07(t_dolar *dol, char *s, char *tmp, t_path *path)
{
    char *tmp2;
    char *tmp3;
    int p;

    if(!(tmp2 = malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
        return (NULL);
    tmp3 = NULL;
    p = dbl_quote(s, dol->i + 1) + 1;
    while (dol->i < p && s[dol->i])
    {
        dol->k = 0;
        dol->w = 0;
        if ((s[dol->i] == '$' && s[dol->i + 1] == '?') || (s[dol->i] == '$' && (s[dol->i + 1] == '\0' || s[dol->i + 1] == '\n')))
            tmp2 = join_dolar(tmp, case_00(dol, path, s)->s1);
        else if (s[dol->i] == '$' && is_valid(s[dol->i + 1]))
        {
            if(!(dol->tmp1 = malloc(sizeof(char) * (in_dollar(s, dol->i) + 1))))
                return (NULL);
            dol->w = count_dolars(s, dol->i);
            if (dol->w % 2 != 0)
                tmp2 = case_01(dol, s, dol->tmp1, path)->s1;
            else
                tmp2 = case_02(dol, s, dol->tmp1)->s1;
            tmp3 = join_dolar(tmp3, tmp2);
            if (s[dol->i] != '\0')
                --dol->i;
        }
        else if (((s[dol->i] != '$') || (s[dol->i] == '$' && s[dol->i + 1] == '\\') || (s[dol->i] == '$' && is_valid(s[dol->i + 1]) == 0)) && s[dol->i])
        {

            if(!(dol->tmp = malloc(sizeof(char) * (until_dollar(s, dol->i) + 1))))
                return (NULL);
            if ((s[dol->i] == '$' && s[dol->i + 1] == '\\') || s[dol->i] == '\\')
            {
                tmp2 = case_04(dol, s, dol->tmp)->s1;
                tmp3 = join_dolar(tmp3, tmp2);
            }
            else
            {
                while (((s[dol->i] != '$' && s[dol->i] != '\\') || (s[dol->i] == '$' && is_valid(s[dol->i + 1]) == 0)) && s[dol->i] && dol->i < p)
                    tmp[dol->k++] = s[dol->i++];
                tmp[dol->k] = '\0';
                tmp3 = join_dolar(tmp3, tmp);
            }

            if (s[dol->i] != '\0')
                --dol->i;
        }
        dol->i++;
        dol->res_tmp = creat_tmp(tmp3);
    }
    return (dol->res_tmp);
}