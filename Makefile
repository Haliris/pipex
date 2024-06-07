# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 12:36:12 by jteissie          #+#    #+#              #
#    Updated: 2024/06/07 14:19:41 by jteissie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = src/

INCLUDE = include/

LIBFT_DIR = libft/

SRC_FILES =

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)
