/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:15:47 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/28 09:21:08 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *define_each(t_list_cmd *lst, t_shell *sh, t_path *path)
{
    char *string;
    char *red;

    if (search(lst->cmd) == 1)
    {
        string = is_befor_redirection(lst->cmd, sh);
        red = is_after_redirection(lst->cmd, sh);
        lst = parsing_red(lst, string, red, path);
    }
    else
        lst = spl_cmd(lst, sh, path);
    return (lst);
}

t_list_cmd *spl_cmd(t_list_cmd *lst, t_shell *sh, t_path *path)
{
    char *string;
    char **free_sp;
    char *cmd;
    char *arg;
    t_all *new1;

    string = ft_strdup(lst->cmd);
    if (string == NULL)
    {
        cmd = NULL;
        arg = NULL;
    }
    else
    {
        free_sp = shell_space_split(string);
        cmd = free_sp[0];
        arg = concat(free_sp, 1);
        free_array(free_sp, count_line(free_sp));
    }
    new1 = s_cmd_details1(cmd, arg);
    add_all(&lst->all, new1);
    return (lst);
}
