/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:47:07 by ntan              #+#    #+#             */
/*   Updated: 2022/05/23 21:03:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	left_arrow(t_prog *cub3d, double angle)
{
	cub3d->pa -= angle;
	if (cub3d->pa < 0)
		cub3d->pa += 2 * PI;
	cub3d->pdx = cos(cub3d->pa) * 4;
	cub3d->pdy = sin(cub3d->pa) * 4;
	cub3d->plane_x = cos(cub3d->pa + PI / 2) * 4;
	cub3d->plane_y = sin(cub3d->pa + PI / 2) * 4;
}

void	right_arrow(t_prog *cub3d, double angle)
{
	cub3d->pa += angle;
	if (cub3d->pa > 2 * PI)
		cub3d->pa -= 2 * PI;
	cub3d->pdx = cos(cub3d->pa) * 4;
	cub3d->pdy = sin(cub3d->pa) * 4;
	cub3d->plane_x = cos(cub3d->pa + PI / 2) * 4;
	cub3d->plane_y = sin(cub3d->pa + PI / 2) * 4;
}

void space(t_prog *cub3d)
{
	if (door_is_close(cub3d) == 1)
		move_door(cub3d);
	// if (cub3d->animation == 0)
	// 	cub3d->animation = 1;	
}

int lock_input(t_prog *cub3d)
{
	if (cub3d->door_state >= 2 && cub3d->door_state <= 5)
		return (-1);
	return (1);
}

int	input(int key, t_prog *cub3d)
{
	if (key == ESC || key == 65307)
		ending(cub3d);
	else if (key == KEY_UP)
		key_up(cub3d);
	else if (key == KEY_DOWN)
		key_down(cub3d);
	else if (key == KEY_LEFT)
		key_left(cub3d);
	else if (key == KEY_RIGHT)
		key_right(cub3d);
	else if (key == RIGHT_ARROW)
		right_arrow(cub3d, 0.1);
	else if (key == LEFT_ARROW)
		left_arrow(cub3d, 0.1);
	else if (key == ESP && cub3d->openable_door_x != -1)
		space(cub3d);
	return (0);
}
