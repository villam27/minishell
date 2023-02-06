# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 23:55:26 by alboudje          #+#    #+#              #
#    Updated: 2023/02/04 11:52:25 by tibernot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
SRC			=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_rsplit.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_printf.c \
				ft_putnbrbase_fd.c \
				ft_ullputnbrbase_fd.c \
				ft_uputnbr_fd.c \
				ft_strtoi.c \
				ft_isspace.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstclear.c \
				ft_lstmap.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_strcmp.c

HEADERS		=	libft.h
AR			=	ar
ARFLAGS 	=	-rcs
OBJ			=	${SRC:.c=.o}
CFLAGS		=	#-Wall -Werror -Wextra
CC			=	gcc

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@printf '$(GREEN)Creating $(CYAN)$(NAME)$(END): OK\n'

%.o : %.c $(HEADERS) Makefile
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf '$(GREEN)Compiling $(NAME): $(CYAN)$<: $(GREEN)OK$(END)\n'

clean :
	-rm -f $(OBJ)

fclean : clean
	-rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re

END=\x1b[0m
BOLD=\x1b[1m
UNDER=\x1b[4m
REV=\x1b[7m

# Colors
GREY=\x1b[30m
RED=\x1b[31m
GREEN=\x1b[32m
YELLOW=\x1b[33m
BLUE=\x1b[34m
PURPLE=\x1b[35m
CYAN=\x1b[36m
WHITE=\x1b[37m

# Colored backgrounds
IGREY=\x1b[40m
IRED=\x1b[41m
IGREEN=\x1b[42m
IYELLOW=\x1b[43m
IBLUE=\x1b[44m
IPURPLE=\x1b[45m
ICYAN=\x1b[46m
IWHITE=\x1b[47m
