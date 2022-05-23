/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:47:07 by ntan              #+#    #+#             */
/*   Updated: 2022/05/23 16:38:46 by cdine            ###   ########.fr       */
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
	update(cub3d);
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
	update(cub3d);
}

void	space(t_prog *cub3d)
{
	int i = 0;

	printf("Cesame ouvre toi\n");
	if (cub3d->map[cub3d->openable_door_y][cub3d->openable_door_x] == '2')
	{
		while (i < 60)
		{
			if (i < 10)
				cub3d->door_state = 1;
			else if (i < 20)
				cub3d->door_state = 2;
			else if (i < 30)
				cub3d->door_state = 3;
			else if (i < 40)
				cub3d->door_state = 4;	
			else if (i < 50)
				cub3d->door_state = 5;
			else if (i < 60)
				cub3d->door_state = 6;	
			update(cub3d);
			i++;
		}
		cub3d->map[cub3d->openable_door_y][cub3d->openable_door_x] = '3';
		update(cub3d);
	}
	else
	{
		cub3d->map[cub3d->openable_door_y][cub3d->openable_door_x] = '2';
		while (i < 60)
		{
			printf("%d\n", cub3d->door_state);
			if (i < 10)
				cub3d->door_state = 6;
			else if (i < 20)
				cub3d->door_state = 5;
			else if (i < 30)
				cub3d->door_state = 4;
			else if (i < 40)
				cub3d->door_state = 3;	
			else if (i < 50)
				cub3d->door_state = 2;
			else if (i < 60)
				cub3d->door_state = 1;	
			update(cub3d);
			i++;
		}
		update(cub3d);
	}
	printf("%s\n", cub3d->map[cub3d->openable_door_y]);
}

int	input(int key, t_prog *cub3d)
{
	printf("%s\n", cub3d->map[10]);
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
