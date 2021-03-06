/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:27:56 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/06 12:20:05 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *replace_01(char *s, t_path *path)
{

    if (serach_dolar(s) == 1)
        return (((dolar(s, path))));
    else
        return ((ft_strdup(s)));
}
