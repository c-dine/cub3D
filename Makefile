SRC = 	srcs/main.c \
		srcs/mini_gnl.c \
		srcs/memory.c

OBJ = ${SRC:.c=.o}

CC = clang
FLAGS = -Wall -Wextra -Werror
OBJ_BONUS = ${SRC_BONUS:.c=.o}
NAME = cub3D
RM = rm -f

.c.o: cub3D
	  ${CC} ${FLAGS} -c -I. $< -o ${<:.c=.o}

${NAME}: ${OBJ} mlx
		${CC} ${FLAGS} ${OBJ} ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/include/ -o ${NAME}

all: ${NAME}

clean:
		${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
		${RM} ${NAME} 

re: fclean all

mlx:
	make -C ./minilibx