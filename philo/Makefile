# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 12:59:39 by fevunge           #+#    #+#              #
#    Updated: 2026/03/09 19:43:08 by fevunge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=philo
SOURCE_DIR=src
UTIL_DIR=$(SOURCE_DIR)/util
IO_DIR$(SOURCE_DIR)/io
CFLAGS=-Wall -Werror -Wextra

INC=$(INCLUDE_DIR)/philo.h

SRC=$(SOURCE_DIR)/main.c \
	$(SOURCE_DIR)/dinner.c \
	$(SOURCE_DIR)/waiter.c \
	$(UTIL_DIR)/ft_atoi.c \
	$(UTIL_DIR)/ft_strlen.c \
	$(UTIL_DIR)/ft_s_is_digit.c \
	$(IO_DIR)/get_args.c \
	$(IO_DIR)/get_error.c \
	$(IO_DIR)/get_log.c \

OBJ=$(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all