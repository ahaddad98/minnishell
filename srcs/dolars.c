/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:50:18 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/07 10:56:39 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tmp *_dolar_norm(char *s, t_path *path, t_dolar *dol)
{
    dol->k = 0;
    dol->w = 0;
    if (!(dol->tmp1 = malloc(sizeof(char) * (in_dollar(s, dol->i) + 1))))
        return (NULL);
    dol->w = count_dolars(s, dol->i);
    if (dol->w % 2 != 0)
        return (case_01(dol, s, dol->tmp1, path));
    else
        return (case_02(dol, s, dol->tmp1));
}

t_tmp *_dolar_norm1(char *s, t_path *path, t_dolar *dol)
{
    dol->k = 0;
    dol->w = 0;
    if (!(dol->tmp = malloc(sizeof(char) * (until_dollar(s, dol->i) + 1))))
        return (NULL);
    return (_norm_case_007(dol, s, dol->tmp, path));
}

t_tmp *_dolar_norm2(char *s, t_dolar *dol)
{
    dol->k = 0;
    dol->w = 0;

    if (!(dol->tmp = malloc(sizeof(char) * (until_dollar(s, dol->i) + 1))))
        return (NULL);
    if (s[dol->i] == '\'')
    {
        dol->res_tmp = case_03(dol, s, dol->tmp);
        puts(dol->res_tmp->s1);
        dol->o = 1;
    }
    if ((s[dol->i] == '$' && s[dol->i + 1] == '\\') || s[dol->i] == '\\')
    {
        dol->res_tmp = case_04(dol, s, dol->tmp);
        dol->o = 1;
    }
    if (s[dol->i] == '$' && s[dol->i + 1] == '$')
    {
        dol->res_tmp = case_05(dol, s, dol->tmp);
        dol->o = 1;
    }
    if (dol->o != 1)
        dol->res_tmp = case_06(dol, s, dol->tmp);
    return (dol->res_tmp);
}
t_tmp *_dolar_last(char *s, t_path *path, t_dolar *dol)
{
    while (s[dol->i])
    {

        if (_condition_norm(s, dol->i) == 1)
            dol->res_tmp = case_00(dol, path, s);
        else if (s[dol->i] == '$' && s[dol->i + 1] != '\\')
        {
            dol->res_tmp = _dolar_norm(s, path, dol);
            --dol->i;
        }
        else if (s[dol->i] == '\"')
        {
            dol->res_tmp = _dolar_norm1(s, path, dol);
            if (s[dol->i] != '\0')
                --dol->i;
        }
        else if (((s[dol->i] != '$' && s[dol->i] != '\"') || (s[dol->i] == '$' && s[dol->i + 1] == '\\')) && s[dol->i])
        {
            dol->res_tmp = _dolar_norm2(s, dol);
            --dol->i;
        }
        dol->o = 0;
        if (s[dol->i])
            dol->i++;
        add_tmp(&(dol->head), dol->res_tmp);
    }
    return (dol->head);
}

char *dolar(char *str, t_path *path)
{
    t_dolar dol;
    t_tmp *tmp;
    char *s;
    char *tmps;
    char *result;

    s = ft_strdup(str);
    ft_bzero(&dol, sizeof(t_dolar));
    dol.head = _dolar_last(s, path, &dol);
    tmp = dol.head;
    result = NULL;
    tmps = NULL;
    while (dol.head != NULL)
    {
        if (result)
            tmps = result;
        result = join_dolar(result, dol.head->s1);
        if (tmps)
            ft_stringdel(&tmps);
        dol.head = dol.head->next;
    }
    dol.head = tmp;
    free_dolar(&(dol.head));
    // free_dolar(&dol.c1);
    ft_stringdel(&s);
    free_str_dol(&dol);
    return (result);
}
