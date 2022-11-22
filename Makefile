# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 15:08:56 by jeseo             #+#    #+#              #
#    Updated: 2022/11/22 17:48:11 by jeseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
MLX_FLAGS 	= 	-L./mlx -lmlx -framework OpenGL -framework Appkit
NAME		=	./so_long
INC			=	./so_long.h
SRC			=	./main.c\
				./get_next_line.c\
				./get_next_line_utils.c\
				./ft_itoa.c\
				./draw_map.c\
				./event_handler.c\
				./so_long_utils.c\
				./check_utils.c \
				./pars_map.c\

OBJ		=	$(SRC:%.c=%.o)
RM		=	rm -f


all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $^ -I $(INC) -o $@

$(OBJ)	:	$(SRC)
	$(CC) $(CFLAGS) -c $^ -I $(INC)

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re