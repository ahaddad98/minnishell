/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:08:10 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/02 17:54:40 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_var_glob1;

void		sigint_handler(int sig)
{
	int		a;

	if (sig == SIGINT)
	{
		g_var_glob1 = 1;
		ft_putstr_fd("\b\b  \b\b\n\e[1;32mbash$ \e[0;37m", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (g_var_glob1 == 3)
			g_var_glob1 = 2;
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

char		**ft_strdup_2d(char **str)
{
	int			len;
	char		**ret;
	int			i;

	i = 0;
	len = count_line(str);
	ret = malloc(sizeof(char *) * len + 1);
	i = 0;
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void		ctrl_d(t_read *rd, t_path *path)
{
	char		*tmp;

	tmp = NULL;
	if (rd->line[0] == '\0' && !path->dos)
	{
		ft_putendl_fd("exit", 1);
		// ft_free_2dem_arr((void ***)&path->env->fullenv);
		exit(0);
	}
	if (rd->line[path->ret - 1] != '\n')
	{
		path->dos = 1;
		if (path->p)
			path->p = ft_strjoin(path->p, rd->line);
		else
			path->p = ft_strdup(rd->line);
	}
	else if (path->p && rd->line[path->ret - 1] == '\n')
	{
		tmp = path->p;
		path->p = ft_strjoin(path->p, rd->line);
		free(tmp);
		rd->line = ft_strdup(path->p);
		// free_1d(path->p);
		if (path->p)
		{
			free(path->p);
			path->p = NULL; 
		}
		// if (tmp)
		// {
		// 	free(tmp);
		// 	tmp = NULL;
		// }
		// puts(rd->line);
		path->dos = 0;
	}
}

void		ft_exe(t_shell *sh, t_path *path, t_list_cmd *lst, t_read *rd)
{
	if (sh->error != 1 && !path->dos)
	{
		if (g_var_glob1 == 1)
		{
			path->dol_sign = 1;
			g_var_glob1 = 0;
		}
		if (g_var_glob1 == 2)
		{
			path->dol_sign = 131;
			g_var_glob1 = 0;
		}
		if (g_var_glob1 == 0)
			g_var_glob1 = 3;
		lst = handle_line(rd, lst, path);
		if (check_one(rd->line) == 1)
			pipes_cmd1(path, lst, sh);
		else if (check_one(rd->line) == 3)
			call_pipe(lst, path, sh);
		else
			call_getprg(lst, path, sh);
	}
	else
		path->dol_sign = 258;
}

void		get_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}

int			main(int argc, char **argv, char **env)
{
	t_read			rd;
	t_shell			sh;
	t_list_cmd		lst;
	t_path			path;

	g_var_glob1 = 0;
	(void)argc;
	init(&path);
	get_signals();
	path.p = NULL;
	path.env->fullenv = ft_strdup_2d(env);
	while (1)
	{
		if (!path.dos && g_var_glob1 != 1)
			ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 1);
		rd.line = malloc(sizeof(char) * BUFFER_SIZE);
		path.ret = read(0, rd.line, BUFFER_SIZE);
		ctrl_d(&rd, &path);
		if (rd.line[0] != '\n')
		{
			sh_initial(&lst, &sh);
			check_line_error(rd.line, &sh);
			ft_exe(&sh, &path, &lst, &rd);
			if (g_var_glob1 == 2)
				ft_putstr_fd("Quit: 3\n", 1);
		}
		// if (rd.line)
		// {
			free(rd.line);
			rd.line = NULL;
		// }
	}
}
