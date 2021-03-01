NAME= minishell
SRC_PATH= srcs
HDR_PATH= includes
OBJ_PATH= obj
LIB_PATH= libft


SRC_NAME=init.c\
		search_env.c\
		env.c\
		minishell.c\
		read_line.c\
		pwd.c\
		execute.c\
		tools.c\
		cd.c\
		shift.c\
		var_env.c\
		export.c\
		unset.c\
		pipes.c\
		echo.c\
		exit.c\
		ft_execute1.c\
		epxort_tools.c\
		pipes1.c\
		shift_tools.c\
		pipes_tools.c\
		main.c\
		read.c\
		lanch.c\
		parsing.c\
		get_next_line.c\
		get_next_line_utils.c\
		pipe.c\
		condition_check_0.c\
		condition_check_1.c\
		condition_check_2.c\
		is_after_redirection.c\
		is_before_redirection.c\
		errors.c\
		comand_details.c\
		redirection_filename.c\
		sort_seperators_all.c\
		minishell_space.c\
		minishell_split.c\
	 	list_creat.c\
		list_add.c\
		list_modify.c\
		print.c\
		simple_cmd_pars.c\
		pars_conditions.c\
		concats.c\
		redirection_sign.c\
		pipe_sort.c\
		comma_or_pipe_sort.c\
		split_tools.c\
		redirection_tools.c\
		free.c\
		dolars.c\
		dolars_1.c\
		dolars_2.c\
		no_quote.c\
		replace.c\
		spl_cmd.c\
		ft_strstr.c\


HDR_NAME=minishell.h 

OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

LIB= libft.a
FLAGS= 
LLIB_FLAG= -L$(LIB_PATH) libft/libft.a
H_FLAG= -I $(HDR_PATH)
#***************************************************************************** #

COMP= gcc

all: lib  $(NAME) 

$(NAME) : $(LIB_PATH)/$(LIB) $(OBJ)
	@rm -rf minishell
	@$(COMP) -g $(H_FLAG) $(OBJ) $(LLIB_FLAG) -o $@

lib:
	@make -sC $(LIB_PATH)

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP)  $(FLAGS) $(H_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIB_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_PATH)
	@echo "\033[0;31m>> $(NAME) && all obbjects are deleted.\033[0m" 

re : fclean all
