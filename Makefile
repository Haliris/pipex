# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 12:36:12 by jteissie          #+#    #+#              #
#    Updated: 2024/06/17 09:15:47 by jteissie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CCFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT = libft/

INCLUDE = 	-I include/ \
	       	-I libft/

SRC =		src/pipex.c \
			src/get_execpaths.c \
			src/utils.c \
			src/execute_path.c

BONUS =		bonus/pipex_bonus.c \
			bonus/get_execpaths_bonus.c \
			bonus/utils_bonus.c \
			bonus/execute_path_bonus.c \
			bonus/process_here_doc_bonus.c \
			bonus/get_next_line/get_next_line_bonus.c \
			bonus/get_next_line/get_next_line_utils_bonus.c \
			bonus/open_utils_bonus.c

OBJ_DIR = obj/

OBJ_FILES =	pipex.o \
		get_execpaths.o \
		utils.o \
		execute_path.o

BONUS_OBJ_FILES = pipex_bonus.o \
				get_execpaths_bonus.o \
				utils_bonus.o \
				execute_path_bonus.o \
				process_here_doc_bonus.o \
				get_next_line_bonus.o \
				get_next_line_utils_bonus.o \
				open_utils_bonus.o

OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

BONUS_OBJ = $(addprefix $(OBJ_DIR), $(BONUS_OBJ_FILES))

all: $(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $@

$(OBJ_DIR)%.o: bonus/%.c | $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $@

$(NAME): $(OBJ) 
	make -C $(LIBFT) all
	$(CC) $(CCFLAGS) $(OBJ) -L./$(LIBFT) -lft -o $(NAME)

bonus: $(BONUS_OBJ)
	make -C $(LIBFT) all
	$(CC) $(CCFLAGS) $(BONUS_OBJ) -L./$(LIBFT) -lft -o $(NAME)

clean:
	make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(LIBFT)libft.a
	rm -f $(NAME) 

re : fclean clean all

.PHONY : all clean fclean re
