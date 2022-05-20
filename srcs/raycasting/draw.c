/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/20 17:26:04 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

u_int32_t	getTexel(t_image img, int x, int y)
{
	int	i;
	int	j;

	i = x  * 4;
	j = 0;
	// printf("%d %d\n", x, y);
	while (j < y)
	{
		i += img.line_length;
		j++;
	}
	// printf("%d %d %d\n", img.addr[i], img.addr[i + 1], img.addr[i + 2]);
	return (getColorRGB(img.addr[i + 2], img.addr[i + 1], img.addr[i]));
}

// 0 = west, 1 = east, 2 = north, 3 = south
void	drawWall(t_prog *cub3d, t_raycast *tmp, float x)
{
	if (tmp->side == 0 || tmp->side == 1) 
		tmp->wallX = cub3d->py + tmp->perpWallDist * tmp->rayDirY;
	else
	    tmp->wallX = cub3d->px + tmp->perpWallDist * tmp->rayDirX;
	tmp->wallX -= floor((tmp->wallX));

	//x coordinate on the texture
	tmp->texX = (int) (tmp->wallX * (double) PXLS);
	if ((tmp->side == 0 || tmp->side == 1) && tmp->rayDirX > 0)
		tmp->texX = PXLS - tmp->texX - 1;
	if ((tmp->side == 2 || tmp->side == 3) && tmp->rayDirY < 0)
		tmp->texX = PXLS - tmp->texX - 1;

	double step = 5.0 * PXLS / tmp->lineHeight;
	// Starting texture coordinate
	double texPos = (tmp->drawStart - SCREEN_H / 2 + tmp->lineHeight / 2) * step;
	int	y;
	u_int32_t	color;

	y = tmp->drawStart;
	while (y < tmp->drawEnd)
	{
		tmp->texY = (int) texPos & (PXLS - 1);
		texPos += step;
		if (tmp->side == 0)
			color = getTexel(cub3d->we_text_img, tmp->texX, tmp->texY);
		else if (tmp->side == 1)
			color = getTexel(cub3d->ea_text_img, tmp->texX, tmp->texY);
		else if (tmp->side == 2)
			color = getTexel(cub3d->no_text_img, tmp->texX, tmp->texY);
		else if (tmp->side == 3)
			color = getTexel(cub3d->so_text_img, tmp->texX, tmp->texY);
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->drawStart, color);
		// printf("%d %d %d\n", tmp->texX, tmp->texY, y);
		tmp->drawStart++;
		y++;
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
