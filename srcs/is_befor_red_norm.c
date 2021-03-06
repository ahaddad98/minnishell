/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_befor_red_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:30:54 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/05 17:43:26 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *norm_befor(char **cmd, t_use *use, char **tmp1, char *tmp)
{
    if (cmd[use->i][use->j] != '>' && cmd[use->i][use->j] != '<')
    {
        tmp1 = ft_minishell_split(cmd[use->i], witch_red(cmd[use->i]));
        tmp = replace(tmp, tmp1[0]);
        free_2d_char(&(tmp1), count_line(tmp1));

    }
    if ((cmd[use->i][use->j] == '>' || cmd[use->i][use->j] == '<') && cmd[use->i][use->j])
    {
        while (cmd[use->i][use->j] != '\0' && (cmd[use->i][use->j] != '\\' || cmd[use->i][use->j] != '\'' || cmd[use->i][use->j] != '\"'))
            use->j++;
    }
    while (cmd[use->i][use->j] != '\0')
    {
        while (cmd[use->i][use->j] && cmd[use->i][use->j] != '>' && cmd[use->i][use->j] != '<')
            use->j++;
        if ((cmd[use->i][use->j] == '>' || cmd[use->i][use->j] == '<') && cmd[use->i][use->j + 1] == '\0' && cmd[use->i] != NULL)
            use->i = use->i + 1;
        use->j++;
    }
    return (tmp);
}

int condition_befor(char **cmd, t_use use)
{
    if (use.i == 0 && number_red(cmd[use.i]) == 0)
        return (1);
    if (use.i == 0 && number_red(cmd[use.i]) > 0 && (cmd[use.i][0] != '>' && cmd[use.i][0] != '<'))
        return (1);
    if (condition_1(cmd, use.i) == 1)
        return (1);
    else
        return (0);
}

char *norm_befor1(char **cmd, t_use *use, char **tmp1, char *tmp)
{
    char *d;
    if (use->i == 0 && number_red(cmd[use->i]) == 0)
    {
        tmp = replace(tmp, cmd[use->i]);
    }
    if (use->i == 0 && number_red(cmd[use->i]) > 0 && (cmd[use->i][0] != '>' && cmd[use->i][0] != '<'))
    {
        tmp1 = ft_minishell_split(cmd[use->i], witch_red(cmd[use->i]));
        tmp = replace(tmp, tmp1[0]);
            free_2d_char(&(tmp1), count_line(tmp1));

    }
    if (condition_1(cmd, use->i) == 1)
        use->i = use->i + 1;
    return (tmp);
}

char *befor(char **cmd, char *tmp)
{
    char **tmp1;
    char *res;
    int i = 0;
    t_use use;

    ft_bzero(&use, sizeof(t_use));
    tmp = NULL;
    while (cmd[use.i] != NULL)
    {
        use.j = 0;
        tmp1 = NULL;
        if (condition_befor(cmd, use) == 1)
        {
            i++;
            tmp = norm_befor1(cmd, &use, tmp1, tmp);
        }
        else if (number_red(cmd[use.i]) > 0 && (cmd[use.i][0] != '>' && cmd[use.i][0] != '<') && use.i > 0 && kayna(cmd[use.i - 1]) == 0) //ls <p< o >l && >5> 6>7
        {
            tmp = norm_befor(cmd, &use, tmp1, tmp);
        }
        else if (number_red(cmd[use.i]) == 0 && (use.i >= 1 && kayna(cmd[use.i - 1]) == 0))
        {
            tmp = replace(tmp, cmd[use.i]);
        }
        use.i++;
    }
    // puts(tmp);
    res = ft_strdup(tmp);
    free(tmp);
    if (*cmd)
    free_2d_char(&(cmd), count_line(cmd));
    return (res);
}