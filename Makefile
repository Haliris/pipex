# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 12:36:12 by jteissie          #+#    #+#              #
#    Updated: 2024/06/07 17:20:48 by jteissie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = CC

CCFLAGS = -Wall -Wextra -Werror

NAME = pipex

LIBFT = libft.a

LIBFT_DIR = libft/

SRC_DIR = src/

INCLUDE = -I include/

SRC_FILES = pipex.c \
			get_execpaths.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o) 

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all
	mv ${LIBFT_DIR}${LIBFT}

$(NAME): 
	${LIBFT} $(OBJ) 

%.o: %.c
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $(NAME)

clean: libftclean
	rm -f $(OBJ)

libftclean :
	make -C $(LIBFT_DIR) clean

fclean :
	rm -f $(NAME) $(LIBFT)

re :
	fclean all

.PHONY : all fclean re libftclean
