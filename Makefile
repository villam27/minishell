# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 13:17:41 by alboudje          #+#    #+#              #
#    Updated: 2023/01/30 15:31:27 by tibernot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	minishell
CC 				= 	cc

LIBFT 			= 	libft/libft.a
LIBFT_FILES		= libft/*.h libft/Makefile

SRC_FOLDER		= 	src/
OBJS_FOLDER		=	objs/
SRC_FILES		= 	command.c \
	command_list.c \
	env_var_list.c \
	env_var_list2.c \
	execution.c \
	execution_utils.c \
	execution_utils2.c \
	ft_split_not_in_quotes.c \
	heredoc.c \
	heredoc_utils.c \
	lst_utils.c \
	main.c \
	minishell_utils.c \
	minishell_utils2.c \
	parse_and_split.c \
	parse_and_split_utils.c \
	parse_and_split_utils2.c \
	parse_and_split_utils3.c \
	to_good_cmds.c \
	to_good_cmds_utils.c \
	to_good_cmds_utils2.c \
	parsing_errors.c \
	create_commands.c \
	create_commands_utils.c \
	create_commands_utils2.c \
	create_commands_utils3.c \
	envp.c \
	minisignals.c \
	get_next_line_no_endl.c \
	shlvl.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_export_utils.c \
	builtins/ft_export_utils2.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c

RD_LIB_H=~/usr/include
RD_LIB_A=-L ~/usr/lib/x86_64-linux-gnu/libreadline.a -lreadline

SRC 			= 	$(addprefix $(SRC_FOLDER), $(SRC_FILES))

INCLUDES_FILES 	= 	minishell.h \
					execution.h\
					builtins.h

INCLUDES 		= 	$(addprefix $(SRC_FOLDER), $(INCLUDES_FILES))

OBJ 			= 	${SRC_FILES:.c=.o}
CFLAGS 			= -Wall -Wextra -Werror -g3 -fsanitize=address
OBJS			= 	$(addprefix $(OBJS_FOLDER), $(OBJ))

all : title makelibft $(NAME)

$(NAME) : $(OBJS_FOLDER) $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(RD_LIB_A) $(LIBFT)
	@printf "$(GREEN)Creating $(PURPLE)$(NAME)$(END): OK\n"

$(OBJS_FOLDER)%.o : $(SRC_FOLDER)%.c $(INCLUDES) Makefile
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(RD_LIB_H)
	@printf "$(BLUE)Compiling $(NAME): $(CYAN)$<: $(GREEN)OK$(END)\n"

$(OBJS_FOLDER):
	mkdir $(OBJS_FOLDER)
	mkdir $(OBJS_FOLDER)/builtins

$(LIBFT):
	@make -C libft/

makelibft:
	@make -C libft/

clean :
	-rm -rf $(OBJS_FOLDER)
	-make clean -C libft

fclean : clean
	-rm -f $(NAME)
	-make fclean -C libft

re : fclean all

title :
	@printf "$(PURPLE)    __  ________   ______          __         ____		\n"
	@printf	"$(PURPLE)   /  |/  /  _/ | / /  _/    _____/ /_  ___  / / /		\n"
	@printf "$(PURPLE)  / /|_/ // //  |/ // /_____/ ___/ __ \\/ _ \\/ / /		\n"
	@printf "$(PURPLE) / /  / // // /|  // /_____(__  ) / / /  __/ / /	 		\n"
	@printf "$(PURPLE)/_/  /_/___/_/ |_/___/    /____/_/ /_/\\___/_/_/   $(END)	\n"
	@printf "___________________________$(RED)tibernot & alboudje$(END)_\n"

.PHONY: all clean fclean re title makelibft

END		=\x1b[0m
BOLD	=\x1b[1m
UNDER	=\x1b[4m
REV		=\x1b[7m

# Colors
GREY	=\x1b[30m
RED		=\x1b[31m
GREEN	=\x1b[32m
YELLOW	=\x1b[33m
BLUE	=\x1b[34m
PURPLE	=\x1b[35m
CYAN	=\x1b[36m
WHITE	=\x1b[37m

# Colored backgrounds
IGREY	=\x1b[40m
IRED	=\x1b[41m
IGREEN	=\x1b[42m
IYELLOW	=\x1b[43m
IBLUE	=\x1b[44m
IPURPLE	=\x1b[45m
ICYAN	=\x1b[46m
IWHITE	=\x1b[47m
