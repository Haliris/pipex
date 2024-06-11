# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 12:36:12 by jteissie          #+#    #+#              #
#    Updated: 2024/06/11 17:47:33 by jteissie         ###   ########.fr        #
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
	error_handler.c

SRC_DIR = ./

BONUS_SRC =	pipex_bonus.c \
		get_execpaths_bonus.c \
		utils_bonus.c

OBJ_DIR = obj/

OBJ_FILES =	pipex.o \
		get_execpaths.o \
		utils.o \
		error_handler.o

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

BONUS_OBJ_FILES = pipex_bonus.o \
		  get_execpaths_bonus.o \
		  utils_bonus.o

BONUS_OBJS = $(addprefix $(OBJ_DIR), $(BONUS_OBJ_FILES))

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

re : fclean all

.PHONY : all clean fclean re
