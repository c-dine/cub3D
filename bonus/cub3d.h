/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:48:03 by ntan              #+#    #+#             */
/*   Updated: 2022/05/23 15:47:11 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "sys/uio.h"
# include "sys/types.h"
# include "fcntl.h"
# include "unistd.h"
# include "minilibx/mlx.h"

# define PXLS 16
# define SCREEN_H 720
# define SCREEN_W 1280
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_LEFT 97
# define KEY_RIGHT 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define RESET 15
# define ESC 53
# define ESP 32

# define PI 3.14159265359

# define RED 0xFF3333
# define BLUE 0x3734eb
# define GREEN 0x3d9c06
# define YELLOW 0xf0c024

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	int		line_height;
	int		draw_start;
	int		draw_end;

	double	wall_x;
	int		tex_x;
	int		tex_y;

	double	tmp_pdx;
	double	tmp_pdy;
}				t_raycast;

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
	int	hex_color;
}				t_color;

typedef struct s_prog
{
	int		door_state;
	int		openable_door_x;
	int		openable_door_y;

	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;

	t_image	no_text_img;
	t_image	so_text_img;
	t_image	we_text_img;
	t_image	ea_text_img;
	t_image	door1;
	t_image	door2;
	t_image	door3;
	t_image	door4;
	t_image	door5;
	t_image	door6;

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
	double	plane_x;
	double	plane_y;
	double	pa;

	t_image	tmp_img;
	t_image	minimap_ext;
	t_image	minimap_int;
}				t_prog;

typedef struct s_drawmap
{
	int	x;
	int	y;
	int	x_map;
	int	y_map;
	int	tmp;
	int	xmap_tmp;
}				t_drawmap;

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
int			check_error(char **file, t_prog *cub3d);
int			ft_checkextension(char *file);

/** PARSING **/
void		init_prog(t_prog *cub3d);
char		**get_file_content(char *file);
int			get_wall_texture(t_prog *cub3d, char *line);
int			get_f_c_texture(t_prog *cub3d, char *line);
int			get_map(t_prog *cub3d, char **map, int line);
void		get_size_map(t_prog *cub3d, char **map);
void		replace_spaces(char **map);
void		replace_backslash_n(char **map);
void		get_player_infos(t_prog *cub3d, int i, int j, char c);
void		map_error_msg(int type);

/** UTILS **/
char		*gnl(int fd);
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isline(char *str);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *dest, char *src);
int			getcolorrgb(int r, int g, int b);
int			getcolortrgb(int t, int r, int g, int b);

void		newimage(t_prog *cub3d);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);

/** GAMING **/
int			game_loop(t_prog *cub3d);
void		init_window(t_prog *cub3d, int widht, int height, char *name);
t_image		create_sprite(t_prog *cub3d, void *mlx, char *path);
int			ending(t_prog *cub3d);
int			draw_map(t_prog *cub3d);
int			draw_player(t_prog *cub3d);
void		key_right(t_prog *cub3d);
void		key_left(t_prog *cub3d);
void		key_down(t_prog *cub3d);
void		key_up(t_prog *cub3d);
int			input(int key, t_prog *cub3d);
int			update(t_prog *cub3d);
int			mouse_hook(t_prog *cub3d);
void		left_arrow(t_prog *cub3d, double angle);
void		right_arrow(t_prog *cub3d, double angle);

/** RAYCASTING **/
int			raycasting(t_prog *cub3d);
void		drawwalls(t_prog *cub3d, t_raycast *tmp, float x);
void		getwalldist(t_raycast *tmp);
void		getsteps(t_prog *cub3d, t_raycast *tmp);
void		initvarray(t_prog *cub3d, t_raycast *tmp, float x);

#endif