/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:26:39 by ntan              #+#    #+#             */
/*   Updated: 2022/05/20 16:47:25 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int draw_map(t_prog *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->map_y)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map[y]))
		{
			if (cub3d->map[y][x] == '1')
				mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->minimap_ext.image, x * PXLS, y * PXLS);
			else
				mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->minimap_int.image, x * PXLS, y * PXLS);
			x++;
		}
		y++;
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
			mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->px + j, cub3d->py + i, RED);
			j++;
		}
		i++;
	}
	k = 0;
	while (k < 5)
	{
		mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->px + cub3d->pdx * k, cub3d->py + cub3d->pdy * k, RED);
		k++;
	}
	return (0);
}

int update(t_prog *cub3d)
{
	void	*tmp;

	tmp = cub3d->tmp_img.image;
	newImage(cub3d);
	raycasting(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->tmp_img.image, 0,0);
	draw_map(cub3d);
	draw_player(cub3d);
	if (tmp)
		mlx_destroy_image(cub3d->mlx, tmp);
	return (0);
}

int	ending(t_prog *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->minimap_ext.image);
	mlx_destroy_image(cub3d->mlx, cub3d->minimap_int.image);
	mlx_destroy_image(cub3d->mlx, cub3d->tmp_img.image);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	memrelease();
	exit(0);
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
	update(cub3d);
}

int	input(int key, t_prog *cub3d)
{
	if (key == ESC || key == 65307)
		ending(cub3d);
	else if (key == KEY_UP)
	{
		if (cub3d->map[(int)(cub3d->py + cub3d->pdy) / PXLS][(int)(cub3d->px + cub3d->pdx) / PXLS] == '0')
		{
			cub3d->px += cub3d->pdx / 5;
			cub3d->py += cub3d->pdy / 5;
			update(cub3d);
		}
	}
	else if (key == KEY_DOWN)
	{
		if (cub3d->map[(int)(cub3d->py - cub3d->pdy) / PXLS][(int)(cub3d->px - cub3d->pdx) / PXLS] == '0')
		{
			cub3d->px -= cub3d->pdx / 5;
			cub3d->py -= cub3d->pdy / 5;
			update(cub3d);
		}
	}
	else if (key == KEY_LEFT)
	{
		if (cub3d->map[(int)(cub3d->py - cub3d->pdx) / PXLS][(int)(cub3d->px + cub3d->pdy) / PXLS] == '0')
		{
			cub3d->px += cub3d->pdy / 5;
			cub3d->py -= cub3d->pdx / 5;
			update(cub3d);
		}
	}
	else if (key == KEY_RIGHT)
	{
		if (cub3d->map[(int)(cub3d->py + cub3d->pdx) / PXLS][(int)(cub3d->px - cub3d->pdy) / PXLS] == '0')
		{
			cub3d->px -= cub3d->pdy / 5;
			cub3d->py += cub3d->pdx / 5;
			update(cub3d);
		}
	}
	else if (key == RIGHT_ARROW)
	{
		cub3d->pa += 0.1;
		if (cub3d->pa > 2 * PI)
			cub3d->pa -= 2 * PI;
		cub3d->pdx = cos(cub3d->pa) * 5;
		cub3d->pdy = sin(cub3d->pa) * 5;
		cub3d->planeX = cos(cub3d->pa + PI / 2) * 5;
		cub3d->planeY = sin(cub3d->pa + PI / 2) * 5;
		update(cub3d);
	}
	else if (key == LEFT_ARROW)
	{
		cub3d->pa -= 0.1;
		if (cub3d->pa < 0)
			cub3d->pa += 2 * PI;
		cub3d->pdx = cos(cub3d->pa) * 5;
		cub3d->pdy = sin(cub3d->pa) * 5;
		cub3d->planeX = cos(cub3d->pa + PI / 2) * 5;
		cub3d->planeY = sin(cub3d->pa + PI / 2) * 5;
		update(cub3d);
	}
	// printf("%f %f %f %f %f\n", cub3d->px, cub3d->py, cub3d->pdx, cub3d->pdy, cub3d->pa);
	return (0);
}

int	game_loop(t_prog *cub3d)
{
	cub3d->pdx = cos(cub3d->pa) * 5;
	cub3d->pdy = sin(cub3d->pa) * 5;
	cub3d->planeX = cos(cub3d->pa + PI / 2) * 5;
	cub3d->planeY = sin(cub3d->pa + PI / 2) * 5;
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (1);
	cub3d->minimap_ext = create_sprite(cub3d, cub3d->mlx, "srcs/game/11.xpm");
	cub3d->minimap_int = create_sprite(cub3d, cub3d->mlx, "srcs/game/12.xpm");
	cub3d->no_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->no_text);
	cub3d->so_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->so_text);
	cub3d->we_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->we_text);
	cub3d->ea_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->ea_text);
	init_window(cub3d, 1280, 720, "cub3d");
	mlx_do_key_autorepeaton(cub3d->mlx);
	mlx_hook(cub3d->win, 17, 0, ending, cub3d);
	mlx_key_hook(cub3d->win, input, cub3d);
	mlx_hook(cub3d->win, 2, (1L << 0), input, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}

