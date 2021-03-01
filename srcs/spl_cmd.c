/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:15:47 by zdnaya            #+#    #+#             */
/*   Updated: 2021/02/26 16:13:31 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd *define_each(t_list_cmd *lst, t_shell *sh, t_path *path)
{

    char *string;
    char *red;
    t_all *new1;
    char **tmp;
    t_use use;
    int i = 0;

    if (search(lst->cmd) == 1)
    {
        string = is_befor_redirection(lst->cmd, sh);
        red = is_after_redirection(lst->cmd, sh);
        lst = define_each1_01(lst, string, red, path);
    }
    else
    {

        lst = sort_all_1(lst, sh, path);
    }

    return (lst);
}

t_list_cmd *sort_all_1(t_list_cmd *lst, t_shell *sh, t_path *path)
{
    char *string;
    char **free_sp;
    char *cmd;
    char *arg;
    t_all *new1;
    int index = 0;
    string = ft_strdup(lst->cmd);
    free_sp = shell_space_split(string);
    int i;
    int j;

    j = 0;
    i = 0;
    cmd = free_sp[0];
    arg = concat(free_sp, 1);
    new1 = s_cmd_details1(cmd, arg);
    add_all(&lst->all, new1);
    return (lst);
}
