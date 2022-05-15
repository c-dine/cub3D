/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:26:39 by ntan              #+#    #+#             */
/*   Updated: 2022/05/15 17:36:22 by ntan             ###   ########.fr       */
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
	else if (key == KEY_UP || key == 122)
		cub3d->player_y -= 8;
	else if (key == KEY_DOWN || key == 115)
		cub3d->player_y += 8;
	else if (key == KEY_LEFT || key == 113)
		cub3d->player_x -= 8;
	else if (key == KEY_RIGHT || key == 100)
		cub3d->player_x += 8;
	return (0);
}

int draw_map(t_prog *cub3d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < cub3d->map_x * 32)
	{
		while (y < cub3d->map_y * 32)
		{
			if (cub3d->map2[x / 32][y / 32] == 1)
				mlx_pixel_put(cub3d->mlx, cub3d->win, x, y, 0xffffff);
			else
				mlx_pixel_put(cub3d->mlx, cub3d->win, x, y, 0x7a7a7a);
			y++;
		}
		x++;
	}
	return (1);
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
	mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->player_x, cub3d->player_y, 0x7baa73);
	draw_map(cub3d);
	return (0);
}

int	game_loop(t_prog *cub3d)
{
	generate_map(cub3d);
	cub3d->player_x = 100;
	cub3d->player_y = 100;
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (1);
	init_window(cub3d, 1024, 512, "cub3d");
	mlx_hook(cub3d->win, 17, 0 , ending, cub3d);
	mlx_key_hook(cub3d->win, input, cub3d);
	mlx_loop_hook(cub3d->mlx, update, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
