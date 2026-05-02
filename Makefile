# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 12:59:39 by fevunge           #+#    #+#              #
#    Updated: 2026/03/15 20:38:25 by fevunge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=thinker
SOURCE_DIR=src
UTIL_DIR=$(SOURCE_DIR)/util
STRING_UTIL_DIR=$(UTIL_DIR)/string
TIME_UTIL_DIR=$(UTIL_DIR)/time
HEAP_UTIL_DIR=$(UTIL_DIR)/heap
IO_DIR=$(SOURCE_DIR)/io

CFLAGS=-Wall -Werror -Wextra -Iinclude/

INC=$(INCLUDE_DIR)/thinker.h

SRC=$(SOURCE_DIR)/main.c \
	$(SOURCE_DIR)/dinner.c \
	$(SOURCE_DIR)/waiter.c \
	$(SOURCE_DIR)/main.c \
	$(STRING_UTIL_DIR)/ft_atoi.c \
	$(STRING_UTIL_DIR)/ft_strlen.c \
	$(STRING_UTIL_DIR)/ft_s_is_digit.c \
	$(TIME_UTIL_DIR)/ft_time_now.c \
	$(TIME_UTIL_DIR)/ft_usleep.c \
	$(HEAP_UTIL_DIR)/ft_salloc.c \
	$(IO_DIR)/get_args.c \
	$(IO_DIR)/get_error.c \
	$(IO_DIR)/get_log.c 

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all