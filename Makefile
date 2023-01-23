# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 13:17:41 by alboudje          #+#    #+#              #
#    Updated: 2023/01/23 15:58:11 by alboudje         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	minishell
CC 				= 	cc

LIBFT 			= 	libft/libft.a
LIBFT_FILES		= 	libft/*.c libft/*.h libft/Makefile

SRC_FOLDER		= 	src/
OBJS_FOLDER		=	objs/
SRC_FILES		= 	main.c \
					command.c \
					command_list.c \
					execution.c \
					execution_utils.c \
					builtins/ft_pwd.c \
					builtins/ft_export.c \
					builtins/ft_export_utils.c \
					builtins/ft_unset.c \
					builtins/ft_env.c \
					builtins/ft_cd.c \
					builtins/ft_echo.c
					
SRC 			= 	$(addprefix $(SRC_FOLDER), $(SRC_FILES))

INCLUDES_FILES 	= 	minishell.h \
					execution.h \
					builtins.h

INCLUDES 		= 	$(addprefix $(SRC_FOLDER), $(INCLUDES_FILES))

OBJ 			= 	${SRC_FILES:.c=.o}
CFLAGS 			= 	-Wall -Wextra -Werror #-g3 -fsanitize=address
OBJS			= 	$(addprefix $(OBJS_FOLDER), $(OBJ))

all : title $(NAME)

$(NAME) : $(OBJS_FOLDER) $(OBJS)
	@make -C libft
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT)
	@printf "$(GREEN)Creating $(PURPLE)$(NAME)$(END): OK\n"

$(OBJS_FOLDER)%.o : $(SRC_FOLDER)%.c $(INCLUDES) Makefile $(LIBFT_FILES)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(BLUE)Compiling $(NAME): $(CYAN)$<: $(GREEN)OK$(END)\n"

$(OBJS_FOLDER):
	mkdir $(OBJS_FOLDER)
	mkdir $(OBJS_FOLDER)/builtins

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

.PHONY: all clean fclean re

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