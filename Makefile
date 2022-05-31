SRC = 	srcs/main.c \
		srcs/utils/gnl.c \
		srcs/utils/memory.c \
		srcs/utils/mlx.c \
		srcs/utils/fct_utils.c \
		srcs/parsing/error_check.c \
		srcs/parsing/parsing.c \
		srcs/parsing/get_texture.c \
		srcs/parsing/get_map.c \
		srcs/parsing/get_map_utils.c \
		srcs/raycasting/raycasting.c \
		srcs/raycasting/draw.c \
		srcs/game/loop.c \
		srcs/game/init_game.c \
		srcs/game/draw.c \
		srcs/game/input.c \
		srcs/game/input_2.c   
SRC_BONUS =	bonus/srcs/main_bonus.c \
			bonus/srcs/utils/gnl_bonus.c \
			bonus/srcs/utils/memory_bonus.c \
			bonus/srcs/utils/mlx_bonus.c \
			bonus/srcs/utils/ft_list.c \
			bonus/srcs/utils/fct_utils_bonus.c \
			bonus/srcs/parsing/error_check_bonus.c \
			bonus/srcs/parsing/error_check_2_bonus.c \
			bonus/srcs/parsing/parsing_bonus.c \
			bonus/srcs/parsing/get_texture_bonus.c \
			bonus/srcs/parsing/get_map_bonus.c \
			bonus/srcs/parsing/doors.c \
			bonus/srcs/parsing/get_map_utils_bonus.c \
			bonus/srcs/raycasting/raycasting_bonus.c \
			bonus/srcs/raycasting/draw_bonus.c \
			bonus/srcs/raycasting/draw_utils.c \
			bonus/srcs/game/loop_bonus.c \
			bonus/srcs/game/doors.c \
			bonus/srcs/game/init_game_bonus.c \
			bonus/srcs/game/draw_bonus.c \
			bonus/srcs/game/input_bonus.c \
			bonus/srcs/game/punch.c \
			bonus/srcs/game/input_2_bonus.c   

OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
OBJ_BONUS = ${SRC_BONUS:.c=.o}
NAME = cub3D
BONUS_NAME = cub3D_bonus
RM = rm -f

.c.o: cub3D
	  ${CC} ${FLAGS} -c -I. $< -o ${<:.c=.o}

all: mlx ${NAME}

${NAME}: ${OBJ}
		${CC} ${FLAGS} ${OBJ} -lm ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/include/ -o ${NAME}

bonus: mlx ${BONUS_NAME}

${BONUS_NAME}: ${OBJ_BONUS}
		${CC} ${FLAGS} ${OBJ_BONUS} -lm ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/include/ -o ${BONUS_NAME}

clean:
		make -C ./minilibx clean
		${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
		${RM} ${NAME} ${BONUS_NAME}

re: fclean all

mlx:
	make -C ./minilibx