# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 20:41:38 by gpollast          #+#    #+#              #
#    Updated: 2025/05/19 16:14:24 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
AR = ar
CFLAGS = -Wall -Werror -Wextra

SRCS =		ft_printf.c \
			ft_putadress.c \
			ft_putchar_len.c \
			ft_puthex_low.c \
			ft_puthex_up.c \
			ft_putnbr_len.c \
			ft_putstr_len.c \
			ft_putunbr_len.c \
			ft_strchr.c \
			ft_memcpy.c

OBJS = $(SRCS:.c=.o)

################################################################################
#                                                                              #
#                                     RULES                                    #
#                                                                              #
################################################################################

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
