/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:47:07 by ntan              #+#    #+#             */
/*   Updated: 2022/05/26 14:25:04 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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

void	space(t_prog *cub3d)
{
	t_door	*tmp;

	tmp = get_door(cub3d);
	if (tmp)
	{
		if (tmp->is_closed == 1)
			tmp->is_closing = 2;
		else
			tmp->is_closing = 1;
	}
	if (cub3d->punch_animation == 0)
	{
		cub3d->punch_animation = 1;
	}
}

void	c_key(t_prog *cub3d)
{
	if (cub3d->weapons == 0)
		cub3d->weapons = 1;
	else if (cub3d->weapons == 1)
		cub3d->weapons = 0;
}

int	input(int key, t_prog *cub3d)
{
	printf("%d\n", key);
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
	else if (key == ESP)
		space(cub3d);
	else if (key == C)
		c_key(cub3d);
	return (0);
}
