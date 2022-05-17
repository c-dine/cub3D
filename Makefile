SRC = 	srcs/main.c \
		srcs/utils/gnl.c \
		srcs/utils/memory.c \
		srcs/utils/fct_utils.c \
		srcs/parsing/error_check.c \
		srcs/parsing/parsing.c \
		srcs/parsing/get_texture.c \
		srcs/parsing/get_map.c \
		srcs/raycasting/raycasting.c \
		srcs/raycasting/utils.c \
		srcs/game/loop.c

OBJ = ${SRC:.c=.o}

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
OBJ_BONUS = ${SRC_BONUS:.c=.o}
NAME = cub3D
RM = rm -f

.c.o: cub3D
	  ${CC} ${FLAGS} -c -I. $< -o ${<:.c=.o}

${NAME}: ${OBJ} mlx
		${CC} ${FLAGS} ${OBJ} -lm ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/include/ -o ${NAME}

all: ${NAME}

clean:
		make -C ./minilibx clean
		${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
		${RM} ${NAME} 

re: fclean all

mlx:
	make -C ./minilibx