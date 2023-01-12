# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 11:29:10 by ademurge          #+#    #+#              #
#    Updated: 2023/01/12 22:27:30 by ademurge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
BLACK		= $(shell tput -Txterm setaf 0)
RED			= $(shell tput -Txterm setaf 1)
GREEN		= $(shell tput -Txterm setaf 2)
YELLOW		= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	= $(shell tput -Txterm setaf 4)
PURPLE		= $(shell tput -Txterm setaf 5)
BLUE		= $(shell tput -Txterm setaf 6)
WHITE		= $(shell tput -Txterm setaf 7)
RESET		= $(shell tput -Txterm sgr0)

# Name of the executable
NAME						=	cub3d

# Files
SRC							=	src/error.c \
								src/free.c \
								src/main.c \
								src/parse.c \
								src/gnl/get_next_line.c \
								src/gnl/get_next_line_utils.c \
								src/utils/parse_utils.c


LIBFT						=	./src/libft/libft.a

INC							=	-I ./inc/.

OBJS						=	$(SRC:.c=.o)

# Flags
CFLAGS						=	-Wall -Wextra -Werror

RM							=	rm -rf

CC							=	gcc

# Rules
all: 		libft $(NAME)

%o:				%c
				@$(CC) ${CFLAGS} -I./includes -c $< -o ${<:.c=.o}

linux:
					@$(CC) $(CFLAGS) $(INC) $(SRC) $(LIBFT_LINUX) -lreadline -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

$(NAME): libft $(OBJS)
					@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -o $(NAME)
					@echo "$(GREEN)********** Compiled. $(RESET)"

libft:
					@make -C ./src/libft

clean:
					@$(RM) $(OBJS)
					@make clean -C ./src/libft
					@echo "$(PURPLE)********* Objects removed. $(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)
			@echo "$(LIGHTPURPLE)********* Executable removed. $(RESET)"

re: fclean all

.PHONY: all clean fclean re libft