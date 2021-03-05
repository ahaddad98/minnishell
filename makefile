# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/05 19:53:43 by ahaddad           #+#    #+#              #
#    Updated: 2021/03/05 19:53:46 by ahaddad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
SRC_PATH= srcs
HDR_PATH= includes
OBJ_PATH= obj
LIB_PATH= libft


SRC_NAME=init.c\
		search_env.c\
		main_tools.c\
		shift_tools2.c\
		env.c\
		minishell.c\
		read_line.c\
		pwd.c\
		execute.c\
		tools.c\
    	directory.c\
		cd.c\
		shift.c\
		var_env.c\
		export.c\
		unset.c\
		pipes.c\
		read.c\
		lanch.c\
		parsing.c\
		pipe.c\
		echo.c\
		condition_check_0.c\
		condition_check_1.c\
		condition_check_2.c\
		is_after_redirection.c\
		is_before_redirection.c\
		errors.c\
		comand_details.c\
		redirection_sig_fname.c\
		sort_seperators_all.c\
		minishell_space.c\
		minishell_split.c\
	 	list_creat.c\
		list_add.c\
		list_modify.c\
		simple_cmd_pars.c\
		pars_conditions.c\
		concats.c\
		pipe_sort.c\
		comma_or_pipe_sort.c\
		split_tools.c\
		main.c\
		exit.c\
		redirection_tools.c\
		free.c\
		dolars.c\
		no_quote.c\
		replace.c\
		spl_cmd.c\
		ft_strstr.c\
		ft_execute1.c\
		epxort_tools.c\
		pipes1.c\
		shift_tools.c\
		pipes_tools.c\
		is_befor_red_norm.c\
		redirection.c\
		dolars_1.c\
		dolars_2.c\
		 dolar_3.c\
		 dolar_4.c\
		 dolar_5.c\
		free_lst.c\
		no_antislash.c\
		norm_antislach.c\
		print.c\


HDR_NAME=minishell.h 

OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

LIB= libft.a
FLAGS= 
LLIB_FLAG= -L$(LIB_PATH) libft/libft.a
H_FLAG= -I $(HDR_PATH)

COMP= gcc 

all: lib  $(NAME) 

$(NAME) : $(LIB_PATH)/$(LIB) $(OBJ)
	@rm -rf miniRT
	@$(COMP) $(H_FLAG) $(LLIB_FLAG) $(OBJ) -o $@

lib:
	@make -sC $(LIB_PATH)

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) $(FLAGS) $(H_FLAG)  -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_PATH)
	@echo "\033[0;31m>> $(NAME) && all obbjects are deleted.\033[0m" 

re : fclean all
