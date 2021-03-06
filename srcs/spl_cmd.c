/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:15:47 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/05 16:38:34 by sqatim           ###   ########.fr       */
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
 
        // puts(string);
        red = is_after_redirection(lst->cmd, sh);
        lst = parsing_red(lst, string, red, path);
        ft_stringdel(&string);
        ft_stringdel(&red);
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
    }
    new1 = s_cmd_details1(cmd, arg);
    add_all(&lst->all, new1);
    if (free_sp)
        free_2d_char(&(free_sp), count_line(free_sp));
    free(string);
    free(arg);
    return (lst);
}

t_list_cmd *parsing_red(t_list_cmd *lst, char *string, char *red,
                        t_path *path)
{
    char **tmp;
    t_all *tmp1;
    char *frees;
    t_use use;

    ft_bzero(&use, sizeof(t_use));
    if (string == NULL)
    {
        use.cmd = NULL;
        use.arg = NULL;
    }
    else
    {
        tmp = shell_space_split(string);
        use.cmd = ft_strdup(tmp[0]);
        use.arg = concat(tmp, 1);
    }
    tmp1 = s_cmd_details((use.cmd), (use.arg), red);
    add_all(&lst->all, tmp1);
    lst = redirection_sort(lst, &use, red);
    if (tmp)
        free_2d_char(&(tmp), count_line(tmp));
    free(use.arg);
    free(use.cmd);
    return (lst);
}