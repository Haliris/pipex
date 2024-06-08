# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 12:36:12 by jteissie          #+#    #+#              #
#    Updated: 2024/06/08 17:52:39 by jteissie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CCFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT = libft/

SRC_DIR = src/

INCLUDE = -I include/ \
		  -I libft/

SRC_FILES = pipex.c \
			get_execpaths.c \
			utils.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = obj/

OBJ_FILES =	pipex.o \
			get_execpaths.o \
			utils.o

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $@

$(NAME): $(OBJ) 
	make -C $(LIBFT) all
	$(CC) $(CCFLAGS) $(OBJ) -L./$(LIBFT) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $@

all: $(NAME)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C $(LIBFT) fclean
	rm -f $(NAME) 

re :
	fclean all

.PHONY : all clean fclean re
