# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 10:53:47 by gpollast          #+#    #+#              #
#    Updated: 2025/07/23 16:45:51 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = 	src/main.c \
		src/parse.c \
		src/process.c \
		src/process_utils.c \
		src/command_utils.c \
		src/fork.c \
		src/get_next_line.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./includes -I./libft -I./ft_printf -g
LDFLAGS = -L./libft -lft -L./ft_printf -lftprintf

all: libft/libft.a ft_printf/libftprintf.a $(NAME)

libft/libft.a:
	@$(MAKE) -C libft bonus

ft_printf/libftprintf.a:
	@$(MAKE) -C ft_printf

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes ./$(NAME) $(ARGS) || true


$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@$(MAKE) -C ft_printf clean
	@echo "Suppression des fichiers objets (project + libft + ft_printf)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C ft_printf fclean
	@echo "Suppression de l'exécutable et des librairies"

re: fclean all