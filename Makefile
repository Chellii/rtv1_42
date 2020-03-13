# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cel-oiri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/12 16:49:38 by cel-oiri          #+#    #+#              #
#    Updated: 2020/02/12 16:49:50 by cel-oiri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
SRC =	main.c \
		all.c \
		camera.c \
		color.c \
		deal_key.c \
		freefct.c \
		insert_obj.c \
		intersection.c \
		list_light.c \
		list_obj.c \
		move.c \
		ray_intersection.c \
		shade.c \
		tools.c \
		verif_format_file.c \
		verif_object.c \
		hit_fct.c \
		vec_op_1.c \
		vec_op_2.c

SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
	C = gcc
	FLAGS = -Wall -Werror -Wextra
	LIB = -L./libft -lft -lmlx -framework OpenGL -framework AppKit
	LIBFT = libft
	LFT = lft
	INC = -I ./
	LIBFT_DIR = ./libft
	LIBFT_LIB = $(LIBFT_DIR)/libft.a
	HEADER = rtv1.h

all: $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT)

$(NAME): $(LIBFT_LIB) $(OBJ)
	$(C) $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(C) $(FLAGS) -o $@ -c $< $(INC)

$(OBJ_DIR):
	@-mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
