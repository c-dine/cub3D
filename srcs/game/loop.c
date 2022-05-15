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
	if (key == ESC)
		ending(cub3d);
	else if (key == KEY_UP)
		cub3d->player_x -= 1;
	else if (key == KEY_DOWN)
		cub3d->player_y += 1;
	else if (key == KEY_LEFT)
		cub3d->player_x -= 1;
	else if (key == KEY_RIGHT)
		cub3d->player_x += 1;
	return (0);
}

int update(t_prog *cub3d)
{
	mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->player_x, cub3d->player_y, 0x7baa73);
	return (0);
}

int	game_loop(t_prog *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (1);
	init_window(cub3d, 1024, 512, "cub3d");
	mlx_hook(cub3d->win, 17, 0 , ending, cub3d);
	mlx_hook(cub3d->win, 2, 0, input, cub3d);
	mlx_loop_hook(cub3d->mlx, update, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
