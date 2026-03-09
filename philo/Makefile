# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fevunge <fevunge@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 12:59:39 by fevunge           #+#    #+#              #
#    Updated: 2026/03/09 13:05:44 by fevunge          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


INCLUDE_DIR=include/
SOURCE_DIR=src/

CC=cc
CFLAGS=-Wall -Werror -Wextra
INCFLAGS=-I$(INCLUDE_DIR)

INC=$(INCLUDE_DIR)/philo.h		\
	$(INCLUDE_DIR)/util.h		\
	$(INCLUDE_DIR)/handler.h	\
	$(INCLUDE_DIR)/service.h	\
	$(INCLUDE_DIR)/resource.h	\

SRC=$(SOURCE_DIR)/philo.c	\
	$(SOURCE_DIR)/util/		\
	$(SOURCE_DIR)/handler/	\
	$(SOURCE_DIR)/service/	\
	$(SOURCE_DIR)/resource/	\

OBJ=$(SRC:.c=.o)


NAME=philo

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(INCFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all