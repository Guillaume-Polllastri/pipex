# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 10:53:47 by gpollast          #+#    #+#              #
#    Updated: 2025/07/04 10:53:51 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = 	main.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./includes -I./libft -g
LDFLAGS = -L./libft -lft

all: libft/libft.a $(NAME)

libft/libft.a:
	@$(MAKE) -C libft

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) $(ARGS) || true


$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@echo "Suppression des fichiers objets (project + libft)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "Suppression de l'exécutable et de la librairie"

re: fclean all