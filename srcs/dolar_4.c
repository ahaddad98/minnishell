/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:23:02 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/01 18:23:40 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *_norm_case07(t_dolar *dol, char *s, char *tmp2, t_path *path)
{
    dol->k = 0;
    dol->w = 0;
    if (!(dol->tmp1 = malloc(sizeof(char) * (in_dollar(s, dol->i) + 1))))
        return (NULL);
    dol->w = count_dolars(s, dol->i);
    if (dol->w % 2 != 0)
        tmp2 = case_01(dol, s, dol->tmp1, path)->s1;
    else
        tmp2 = case_02(dol, s, dol->tmp1)->s1;
    return (tmp2);
}

char *_norm_case007(t_dolar *dol, char *s, char *tmp2, char *tmp3)
{
    dol->k = 0;
    dol->w = 0;
    if (!(dol->tmp = malloc(sizeof(char) * (until_dollar(s, dol->i) + 1))))
        return (NULL);
    if ((s[dol->i] == '$' && s[dol->i + 1] == '\\') || s[dol->i] == '\\')
    {
        tmp2 = case_04(dol, s, dol->tmp)->s1;
        tmp3 = join_dolar(tmp3, tmp2);
    }
    else
    {
        while (((s[dol->i] != '$' && s[dol->i] != '\\') || (s[dol->i] == '$' &&
                                                            is_valid(s[dol->i + 1]) == 0)) &&
               s[dol->i] && dol->i < dol->p)
            dol->tmp[dol->k++] = s[dol->i++];
        dol->tmp[dol->k] = '\0';
        tmp3 = join_dolar(tmp3, dol->tmp);
    }
    return (tmp3);
}
t_tmp *_norm_case_007(t_dolar *dol, char *s, char *tmp, t_path *path)
{
    char *tmp3;
    char *tmp2;
    char *tmpos;

    tmp3 = NULL;
    if (!(tmp2 = malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
        return (NULL);
    dol->p = dbl_quote(s, dol->i + 1) + 1;
    while (dol->i < dol->p && s[dol->i])
    {
        if (_condition_norm(s, dol->i) == 1)
            tmp2 = join_dolar(tmp, case_00(dol, path, s)->s1);
        else if (s[dol->i] == '$' && is_valid(s[dol->i + 1]))
        {
            tmpos = tmp3;
            tmp3 = join_dolar(tmp3, _norm_case07(dol, s, tmp2, path));
            if(tmpos)
                free(tmpos);
            if (s[dol->i] != '\0')
                --dol->i;
        }
        else if (((s[dol->i] != '$') || (s[dol->i] == '$' && s[dol->i + 1] == '\\') || (s[dol->i] == '$' && is_valid(s[dol->i + 1]) == 0)) && s[dol->i])
        {
            tmpos = tmp3;
            tmp3 = _norm_case007(dol, s, tmp2, tmp3);
            if(tmpos)
                free(tmpos);
            if (s[dol->i] != '\0')
                --dol->i;
        }
        dol->i++;
        dol->res_tmp = creat_tmp(tmp3);
    }
    ft_stringdel(&tmp2);
    // ft_stringdel(&tmp3);
    ft_stringdel(&tmp);
    return (dol->res_tmp);
}
