/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:48:03 by ntan              #+#    #+#             */
/*   Updated: 2022/05/18 15:44:01 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sys/uio.h"
#include "sys/types.h"
#include "fcntl.h"
#include "unistd.h"
#include "minilibx/mlx.h"

#define PXLS 16
#define	SCREEN_H 720
#define	SCREEN_W 1280
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363
#define RESET 15
#define ESC 53

#define PI 3.14159265359

typedef struct s_image {
	void	*image;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		size_x;
	int		size_y;
}				t_image;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_prog
{
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;

	t_color	floor;
	t_color	ceiling;

	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;

	char	**map;
	int		map_x;
	int		map_y;
	
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	planeX;
	double	planeY;
	double	pa;

	t_image	minimap_ext;
	t_image minimap_int;
}				t_prog;

/** GARBAGE COLLECTOR **/

# define ERROR 0
# define NOERR 1

typedef struct s_memlst		t_memlst;

struct	s_memlst
{
	void		*address;
	t_memlst	*nxt;
};

int			mempush(void *ptr, const size_t byte, const size_t size);
int			memfree(void *ptr);
int			memrelease(void);

/** ERROR CHECK **/
int	check_error(char **file, t_prog *cub3d);
int	ft_checkextension(char *file);

/** PARSING **/
void	init_prog(t_prog *cub3d);
char	**get_file_content(char *file);
int		get_wall_texture(t_prog *cub3d, char *line);
int		get_f_c_texture(t_prog *cub3d, char *line);
int		get_map(t_prog *cub3d, char **map, int line);

/** UTILS **/
char	*gnl(int fd);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isline(char *str);
char    *ft_strdup(const char *s);
char     *ft_strcpy(char *dest, char *src);

float	degToRad(int angle);
int		fixAngle(int angle);

/** GAMING **/
int		game_loop(t_prog *cub3d);

/** RAYCASTING **/
int		drawRays(t_prog *cub3d);

#endif