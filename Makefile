# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 13:17:41 by alboudje          #+#    #+#              #
#    Updated: 2023/01/19 09:33:27 by ratinax          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	minishell
CC 				= 	gcc

LIBFT 			= 	libft/libft.a
LIBFT_FILES		= 	libft/*.c libft/*.h libft/Makefile

SRC_FOLDER		= 	src/
OBJS_FOLDER		=	objs/
SRC_FILES		= 	main.c \
					parsing_errors.c \
					heredoc.c \
					minishell_utils.c \
					heredoc_utils.c

RD_LIB_H=-I/usr/local/include
#mac #~/.brew/opt/readline/include
RD_LIB_A=-L/usr/local/lib -I/usr/local/include -lreadline
#mac #-L ~/.brew/opt/readline/lib -lreadline

SRC 			= 	$(addprefix $(SRC_FOLDER), $(SRC_FILES))

INCLUDES_FILES 	= 	minishell.h

INCLUDES 		= 	$(addprefix $(SRC_FOLDER), $(INCLUDES_FILES))

OBJ 			= 	${SRC_FILES:.c=.o}
CFLAGS 			= 	-Wall -Wextra -Werror# -g3 -fsanitize=address
OBJS			= 	$(addprefix $(OBJS_FOLDER), $(OBJ))



all : title
	gcc -Wall -Werror -Wextra src/*.c libft/*.c -L/usr/local/lib -I/usr/local/include -lreadline

$(NAME) : $(OBJS_FOLDER) $(OBJS)
	make -C libft
	$(CC) -o $(NAME) $(CFLAGS) $(RD_LIB_A) $(OBJS) $(LIBFT)
	@printf "$(GREEN)Creating $(PURPLE)$(NAME)$(END): OK\n"

$(OBJS_FOLDER)%.o : $(SRC_FOLDER)%.c $(INCLUDES) Makefile $(LIBFT_FILES)
	$(CC) $(CFLAGS) -o $@ -c $< $(RD_LIB_H)
	@printf "$(BLUE)Compiling $(NAME): $(CYAN)$<: $(GREEN)OK$(END)\n"

$(OBJS_FOLDER):
	mkdir $(OBJS_FOLDER)

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
