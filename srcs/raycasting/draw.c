/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/19 19:52:30 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	drawWall(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	i = 0;
	while (i < tmp->lineHeight)
	{
		if (tmp->side == 0)
			my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->drawStart, RED);
		else if (tmp->side == 1)
			my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->drawStart, BLUE);
		else if (tmp->side == 2)
			my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->drawStart, GREEN);
		else
			my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->drawStart, YELLOW);
		tmp->drawStart++;
		i++;
	}
}

void	drawCeiling(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	y;

	y = 0;
	while (y <= (SCREEN_H - tmp->lineHeight) / 2)
	{
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, y, cub3d->ceiling.hex_color);
		y++;
	}
}

void	drawFloor(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	y;

	y = tmp->drawEnd;
	while (y <= SCREEN_H)
	{
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, y, cub3d->floor.hex_color);
		y++;
	}
}

void	drawWalls(t_prog *cub3d, t_raycast *tmp, float x)
{
	drawWall(cub3d, tmp, x);
	drawCeiling(cub3d, tmp, x);
	drawFloor(cub3d, tmp, x);
}
