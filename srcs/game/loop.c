/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:26:39 by ntan              #+#    #+#             */
/*   Updated: 2022/05/17 16:59:39 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int	ending(t_prog *cub3d)
{
	(void)cub3d;
	memrelease();
	exit(0);
	return (0);
}

t_image	create_sprite(t_prog *cub3d, void *mlx, char *path)
{
	t_image	sprite;

	sprite.image = mlx_xpm_file_to_image(mlx, path, &sprite.size_x,
			&sprite.size_y);
	if (!sprite.image)
		ending(cub3d);
	sprite.addr = mlx_get_data_addr(sprite.image, &sprite.bits_per_pixel,
			&sprite.line_length, &sprite.endian);
	return (sprite);
}

void	init_window(t_prog *cub3d, int widht, int height, char *name)
{
	cub3d->win = mlx_new_window(cub3d->mlx, widht, height, name);
	cub3d->win_x = widht;
	cub3d->win_y = height;
}

int	input(int key, t_prog *cub3d)
{
	if (key == ESC || key == 65307)
		ending(cub3d);
	else if (key == KEY_UP)
	{
		if (cub3d->map2[(int)(cub3d->px + cub3d->pdx) / PXLS][(int)(cub3d->py + cub3d->pdy) / PXLS] == '0')
		{
			cub3d->px += cub3d->pdx;
			cub3d->py += cub3d->pdy;
		}
	}
	else if (key == KEY_DOWN)
	{
		if (cub3d->map2[(int)(cub3d->px - cub3d->pdx) / PXLS][(int)(cub3d->py - cub3d->pdy) / PXLS] == '0')
		{
			cub3d->px -= cub3d->pdx;
			cub3d->py -= cub3d->pdy;
		}
	}
	else if (key == KEY_LEFT)
	{
		if (cub3d->map2[(int)(cub3d->px + cub3d->pdy) / PXLS][(int)(cub3d->py - cub3d->pdx) / PXLS] == '0')
		{
			cub3d->px += cub3d->pdy;
			cub3d->py -= cub3d->pdx;
		}
	}
	else if (key == KEY_RIGHT)
	{
		if (cub3d->map2[(int)(cub3d->px - cub3d->pdy) / PXLS][(int)(cub3d->py + cub3d->pdx) / PXLS] == '0')
		{
			cub3d->px -= cub3d->pdy;
			cub3d->py += cub3d->pdx;
		}
	}
	else if (key == LEFT_ARROW)
	{
		cub3d->pa -= 0.1;
		if (cub3d->pa < 0)
			cub3d->pa += 2 * PI;
		cub3d->pdx = cos(cub3d->pa) * 5;
		cub3d->pdy = sin(cub3d->pa) * 5;
	}
	else if (key == RIGHT_ARROW)
	{
		cub3d->pa += 0.1;
		if (cub3d->pa > 2 * PI)
			cub3d->pa -= 2 * PI;
		cub3d->pdx = cos(cub3d->pa) * 5;
		cub3d->pdy = sin(cub3d->pa) * 5;
	}
	printf("%f %f %f %f %f\n", cub3d->px, cub3d->py, cub3d->pdx, cub3d->pdy, cub3d->pa);
	return (0);
}

int draw_map(t_prog *cub3d)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub3d->map_x)
	{
		y = 0;
		while (y < cub3d->map_y)
		{
			if (cub3d->map2[x][y] == '1')
				mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->minimap_ext.image, x * PXLS, y * PXLS);
			else
				mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->minimap_int.image, x * PXLS, y * PXLS);
			y++;
		}
		x++;
	}
	return (1);
}

int	draw_player(t_prog *cub3d)
{
	int	i;
	int j;
	int k;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->px - 3 + i, cub3d->py - 3 + j, 0xFF3333);
			j++;
		}
		i++;
	}
	k = 0;
	while (k < 5)
	{
		mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->px + cub3d->pdx * k, cub3d->py + cub3d->pdy * k, 0xFF3333);
		k++;
	}
	return (0);
}

int generate_map(t_prog *cub3d)
{
	char **map;

	map = malloc(sizeof(char*) * 9);
	map[0] = ft_strdup("1111111111");
	map[1] = ft_strdup("1000000001");
	map[2] = ft_strdup("1111000001");
	map[3] = ft_strdup("1000000001");
	map[4] = ft_strdup("1000000001");
	map[5] = ft_strdup("1000011001");
	map[6] = ft_strdup("1000001001");
	map[7] = ft_strdup("1111111111");
	map[8] = NULL;
	cub3d->map2 = map;
	cub3d->map_x = 8;
	cub3d->map_y = 10;
	return (1);
}

int update(t_prog *cub3d)
{
	mlx_clear_window(cub3d->mlx, cub3d->win);
	draw_map(cub3d);
	draw_player(cub3d);
	drawRays(cub3d);
	return (0);
}

int	game_loop(t_prog *cub3d)
{
	generate_map(cub3d);
	cub3d->pa = 0;
	cub3d->pdx = cos(cub3d->pa) * 5;
	cub3d->pdy = sin(cub3d->pa) * 5;
	cub3d->px = 100;
	cub3d->py = 100;
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (1);
	cub3d->minimap_ext = create_sprite(cub3d, cub3d->mlx, "srcs/game/11.xpm");
	cub3d->minimap_int = create_sprite(cub3d, cub3d->mlx, "srcs/game/12.xpm");
	init_window(cub3d, 1280, 720, "cub3d");
	mlx_do_key_autorepeaton(cub3d->mlx);
	mlx_hook(cub3d->win, 17, 0 , ending, cub3d);
	mlx_key_hook(cub3d->win, input, cub3d);
	mlx_loop_hook(cub3d->mlx, update, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}

