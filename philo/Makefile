# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 12:59:39 by fevunge           #+#    #+#              #
#    Updated: 2026/03/09 14:42:55 by fevunge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #




CC=cc
NAME=philo
SOURCE_DIR=src
CFLAGS=-Wall -Werror -Wextra

INC=$(INCLUDE_DIR)/philo.h		\
	$(INCLUDE_DIR)/util.h		\
	$(INCLUDE_DIR)/handler.h	\
	$(INCLUDE_DIR)/service.h	\
	$(INCLUDE_DIR)/resource.h	\

SRC=$(SOURCE_DIR)/philo.c \
	$(SOURCE_DIR)/util/string_to_int.c \
	$(SOURCE_DIR)/util/string_len.c \
	$(SOURCE_DIR)/handler/error/handler_error.c \
	$(SOURCE_DIR)/handler/in/get_args.c \
	$(SOURCE_DIR)/handler/in/validate_args.c 
#	$(SOURCE_DIR)/service/ \
#	$(SOURCE_DIR)/resource/ \

OBJ=$(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all