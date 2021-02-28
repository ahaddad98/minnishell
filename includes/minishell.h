/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:45:08 by ahaddad           #+#    #+#             */
/*   Updated: 2021/02/28 17:18:04 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <limits.h>
# define BUFFER_SIZE 2048

typedef struct s_env
{
  char **fullenv;
  char *pwd;
  char *oldpwd;
} t_env;

typedef struct s_path
{
  char *path;
  char *cmds;
  char *pathcmd;
  t_env *env;
  char *p;
  char *users;
  int dol_sign;
  int   d;
  int size;
  pid_t pid;
  int file_desc;
  int i;
  int index;
  int			check;
  int ret;
  int dos;
} t_path;

typedef struct s_token
{
  char *token;
  struct s_token *next;
} t_token;

typedef struct s_read
{
  char *line;
  int fd;
} t_read;
typedef struct s_redirection
{
  char *file_name;
  char *sign;
  struct s_redirection *next;
} t_redirection;

typedef struct s_shell
{
  int pipe;
  int comma;
  int count_pipe;
  int count_comma;
  char **simple_cmd;
  int both;
  int redirection;
  char *sh_direct;
  int sp_quote;
  int db_quote;
  int error;
  int _red;
} t_shell;

typedef struct s_all
{
  char *command;
  char *argument;
  char *redirection;
  t_redirection *red;
  struct s_all *next;
} t_all;

typedef struct s_pipe
{
  char *str_pipe;
  char *sh_p_cmd;
  char *sh_p_arg;
  t_all *all;
  struct s_pipe *next;
} t_pipe;

typedef struct s_dol
{
  int dol_s;
} t_dol;

typedef struct s_list_cmd
{
  char *cmd;
  char *sh_cmd;
  char *sh_arg;
  t_pipe *pipe;
  t_all *all;
  struct s_list_cmd *next;
} t_list_cmd;

typedef struct s_line
{
  t_list_cmd *lst;
  t_pipe *pipe;
  t_all *simple_cmd;
  struct s_line *next;
} t_line;

typedef struct s_use
{
  char *string;
  char *red;
  char **free_sp;
  char *cmd;
  char *arg;
  char *sign;
  char *arg1;
  char *file_name;
  int i;
  int j;
  int o;
  int k;
  int w;
  t_redirection *red1;
  t_all *new1;
  int cmd_index;
  char *cmd2;

} t_use;

typedef struct s_tmp
{
  char *s1;
  char *s2;
  struct s_tmp *next;
} t_tmp;

typedef struct s_dolar
{
  int i;
  int k;
  char *tmp1;
  char *tmp;
  char *var;
  char *var_tmp;
  char *result;
  char *two;
  char *s1;
  int len;
  int j;
  int w;
  int u;
  int m;
  t_tmp *head;
  t_tmp *c1;
  t_tmp *res_tmp;
} t_dolar;

/*
**
*************execute*****************
**
*/
void  ft_fd(int fd[2], int fd1[2]);
void		ft_error_free(void);
void		check_fd(int fd[2], int fd1[2], int i, t_path *path);
int lstsize_2(t_redirection *red);
void red_dif(char *f1, char *f2);
int ch_red_dif(t_list_cmd *lst, t_shell *sh);
char **get_reder1(t_all *all);
char **get_antired(t_all *all);
int is_modif(char *args, int ch_mod, t_path *path);
char *get_bef_eq(char *args);
int checkis_valid_var(char *args);
void ft_exit();
int ch_red_dif(t_list_cmd *lst, t_shell *sh);
void init(t_path *path);
void show_env(char **path);
char *search_env(char **env, char *str);
void print_working_directory(t_path *path);
void exeute(t_path *path, char *cmd);
char **ft_space_split_quote(char const *s);
void get_directory(t_path *path);
int check_path(char *path, char *cmd);
void shift_extra(t_path *path, t_all *all, t_shell *sh);
char *get_var_env(t_path *path, char *var);
void cd_cmd(char *nextpath, t_path *path);
int count_line(char **env);
void export_cmd(char *name, char **env, t_shell *sh, t_path *path);
void unset_cmd(char *name, t_path *path);
char *ft_str_to_equal(const char *s1, const char *s2, int len);
void pipes_cmd(t_path *path, t_list_cmd *lst, t_shell *sh);
void pipes_cmd1(t_path *path, t_list_cmd *lst, t_shell *sh);
void ft_echo(char *str, int option, t_path *path);
void call_pipe(t_list_cmd *lst, t_path *path, t_shell *sh);
void call_getprg(t_list_cmd *lst, t_path *path, t_shell *sh);
void show_env1(char **env);
int ft_strcmp(const char *s1, const char *s2);
int lstsize(t_list_cmd *lst);
int lstsize_1(t_list_cmd *lst);
void pipes_cmds(t_path *path, t_list_cmd *lst, int s);
void ft_execute1(t_all *all, t_path *path, t_shell *sh);
void    free_1d(char *p);
void    ft_free_2dem_arr(void ***arr);
void    ft_free_arr(void **array);
/*
**
*************parsing*****************
**
*/
char *ft_strstr(char *str, char *str1);
char **ft_space_split(char const *s);
char *ft_str_in_str(const char *s1, const char *s2);
int ft_2strlen(char **str);
t_token *ft_parse(char *line);
char **ft_split_whitespaces(char *str);
void shift(int fd);
void loop_sh(void);
char *read_line(char *line);
void lanch_cmd(char *line);
int ft_strcmp(const char *s1, const char *s2);
void ft_check_seperator(char *line, t_shell *sh);
void seperat_with_pipe(t_list_cmd *lst);
void ft_check_comma(char *line, t_shell *sh);
void ft_check_pipe(char *line, t_shell *sh);
int pipe_e(char *line, t_shell *sh);
int check_one(char *line);
void print(t_pipe *pipe, t_shell *sh);
void comand_details(t_list_cmd *lst, t_shell *sh, t_path *path);
int check_redirection(char *line);
char *is_befor_redirection(char *line, t_shell *sh);
char *is_after_redirection(char *line, t_shell *sh);
char *ft_str_join(char *s1, char *s2, char *s3);
int search(char *str);
void check_line_error(char *line, t_shell *sh);
char *concat(char **tmp, int i);
void part_one(t_list_cmd *lst, t_shell *sh, t_path *path);
void part_two(t_list_cmd *lst, t_shell *sh, t_path *path);
char *concat_space(char *tmp, char *tmp1);
char *seperat_red(char *tmp);
char *seperat_file_name(char *tmp);
int condition_1(char **free_sp, int i);
int condition_2(char **free_sp, int i);
void condition_3(t_use *use, char ***free_sp);
char quote_char(char *s, t_shell *sh);
char **ft_minishell_split(char const *s, char c);
char **shell_space_split(char const *s);
char *no_quote(char *str);
void sh_initial(t_list_cmd *lst, t_shell *sh);
int we_have_quote(char *str, char c);
// void promp_bash(t_cmd *cmd, t_path *path, int ret, char **line);
void *free_array(char **array, int ligne);
int dbl_quote(const char *line, int i);
int spl_quote(const char *line, int i);
void ft_stringdel(char **string);
//************************RidirectionTools*******/
char *replace(char *tmp, char *s2);
int kayna2(char *str);
int count(char *s);
int count_slach(char *line);
int norm_red(char *line);
int count_from(char *line, int i);
int search_2(char *str);
int kayna(char *str);
int number_red(char *line);
int index_1(char *line, int i);

/*****************LIST***************************/
t_tmp *creat_tmp(char *s1);
void add_tmp(t_tmp **head, t_tmp *new_cmd);
t_list_cmd *handle_line(t_read *rd, t_list_cmd *lst, t_path *path);
t_list_cmd *parsing_red(t_list_cmd *lst, char *string, char *red,
                        t_path *path);
t_all *all_conditions(t_all *all, char **free_sp, int *i);
t_list_cmd *redirection_sort(t_list_cmd *lst, t_use *use, char *free_sp);
t_list_cmd *pars_p_r(t_list_cmd *lst, char *string, char *red,
                     t_path *path);
t_list_cmd *pars_red(t_list_cmd *lst, char *red, t_use *use);
t_list_cmd *pars_pipe(t_list_cmd *lst, t_shell *sh, t_path *path);
t_all *s_cmd_details(char *s1, char *s2, char *s3);
t_list_cmd *define_each1(char *line);
t_redirection *creat_node_r(char *content, char *content1);
void add_red(t_redirection **head, t_redirection *new_cmd);
t_list_cmd *spl_cmd(t_list_cmd *lst, t_shell *sh, t_path *path);
t_list_cmd *sort_all_2(t_list_cmd *lst, t_all *all, char **free_sp, t_path *path);
t_list_cmd *link_list(t_list_cmd *lst, t_shell *sh);
t_list_cmd *simple_cmd(t_list_cmd *lst, char **simple_cmd);
t_all *s_cmd_details1(char *s1, char *s2);
t_all *update_all(char *cmd, char *arg, t_redirection *red);
void add_cmd(t_list_cmd **head, t_list_cmd *new_obj);
t_list_cmd *creat_node(char *content);
t_list_cmd *define_each(t_list_cmd *lst, t_shell *sh, t_path *path);
t_pipe *both(t_list_cmd *lst, t_shell *sh);
t_list_cmd *pipe_define_each(t_list_cmd *lst, t_shell *sh, char **env);
void add_pipe_list(t_pipe **head, t_pipe *new_cmd);
t_pipe *creat_node_p(char *content);
void add_all(t_all **head, t_all *new_cmd);

void print_all(t_list_cmd *lst, t_shell *sh);
/******************DOLAR*************************/
char *replace_01(char *tmp, t_path *path);
int ft_isalpha2(int c);
int until_dollar(char *s, int i);
int in_dollar(char *s, int i);
int strlen_tmp(t_tmp *tmp);       // mo7alna7etajha
int count_dolars(char *s, int i); //7eta hadi
char *join_dolar(char *s1, char *s2);
char *dolar(char *s, t_path *path);
t_tmp *case_07(t_dolar *dol, char *s, char *tmp, t_path *path);
t_tmp *case_06(t_dolar *dol, char *s, char *tmp);
t_tmp *case_05(t_dolar *dol, char *s, char *tmp);
t_tmp *case_04(t_dolar *dol, char *s, char *tmp);
t_tmp *case_03(t_dolar *dol, char *s, char *tmp);
t_tmp *case_02(t_dolar *dol, char *s, char *tmp1);
t_tmp *case_01(t_dolar *dol, char *s, char *tmp1, t_path *path);
t_tmp *case_00(t_dolar *dol, t_path *path, char *s);
int is_valid(char c);
int serach_dolar(char *line);
char *no_antislach(char *str);
char *slach(char *s);
int check_n(char *str);
int ft_strlen_to_char(char *str);
void free_all(t_list_cmd *lst);
char *befor(char **cmd);
char witch_red(char *s);
int dbl_quote_norm(const char *line, int i);
int len_each(const char *s, int i);
int each_char_norm(const char *s, int i, int u, int z);


//// just for test
void print_all(t_list_cmd *lst, t_shell *sh);
#endif
