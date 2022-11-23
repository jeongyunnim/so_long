# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 15:08:56 by jeseo             #+#    #+#              #
#    Updated: 2022/11/23 13:17:56 by jeseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
MLX_FLAGS 	= 	-L./mlx -lmlx -framework OpenGL -framework Appkit

NAME		=	./so_long
NAME_BONUS	=	./so_long_bonus

INC			=	./so_long.h
INC_BONUS	=	./so_long_bonus.h

SRC			=	./main.c\
				./get_next_line.c\
				./get_next_line_utils.c\
				./ft_itoa.c\
				./draw_map.c\
				./event_handler.c\
				./so_long_utils.c\
				./check_utils.c \
				./pars_map.c\

SRC_BONUS	=	./main_bonus.c\
				./get_next_line_bonus.c\
				./get_next_line_utils_bonus.c\
				./ft_itoa_bonus.c\
				./draw_map_bonus.c\
				./event_handler_bonus.c\
				./so_long_utils_bonus.c\
				./check_utils_bonus.c \
				./pars_map_bonus.c\

OBJ			=	$(SRC:%.c=%.o)
OBJ_BONUS	=	$(SRC_BONUS:%.c=%.o)
RM		=	rm -f


all		:	$(NAME)

bonus	:	$(NAME_BONUS)

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $^ -I $(INC) -o $@

$(OBJ)	:	$(SRC)
	$(CC) $(CFLAGS) -c $^ -I $(INC)

$(NAME_BONUS)	:	$(OBJ_BONUS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $^ -I $(INC_BONUS) -o $@

$(OBJ_BONUS)	:	$(SRC_BONUS)
	$(CC) $(CFLAGS) -c $^ -I $(INC)

clean	:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean	:	clean
	$(RM) $(NAME) $(NAME_BONUS)

re		:	fclean all

.PHONY	:	all clean fclean re