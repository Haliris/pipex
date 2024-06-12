# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 12:36:12 by jteissie          #+#    #+#              #
#    Updated: 2024/06/12 18:47:06 by jteissie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CCFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT = libft/

INCLUDE = 	-I ./ \
	       	-I libft/

SRC =	pipex.c \
	get_execpaths.c \
	utils.c \
	execute_path.c

SRC_DIR = ./

OBJ_DIR = obj/

OBJ_FILES =	pipex.o \
		get_execpaths.o \
		utils.o \
		execute_path.o

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $@

$(NAME): $(OBJ) 
	make -C $(LIBFT) all
	$(CC) $(CCFLAGS) $(OBJ) -L./$(LIBFT) -lft -o $(NAME)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C $(LIBFT) fclean
	rm -f $(NAME) 

re : fclean clean all

.PHONY : all clean fclean re
