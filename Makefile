# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/17 17:27:16 by vveselov          #+#    #+#              #
#    Updated: 2018/01/24 21:31:50 by vveselov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

OBJ_DIR = ./

SRC_DIR = ./

INC_DIR = ./

SRC = ft_printf.c spec.c char_spec.c spec_ls.c spec_di.c spec_oux.c spec_p.c \
spec_c.c spec_x.c spec_u.c bonus1.c bonus2.c spec_b.c spec_n.c spec_f.c \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

HEAD = ft_printf.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ_DIR)%.o: %.c
	gcc -c $< -o $@ $(CFLAGS) -I $(INC_DIR)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)