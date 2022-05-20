/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/20 20:10:19 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

u_int32_t	gettexel(t_image img, int x, int y)
{
	int	i;
	int	j;

	i = x * 4;
	j = 0;
	while (j < y)
	{
		i += img.line_length;
		j++;
	}
	return (getcolorrgb(img.addr[i + 2], img.addr[i + 1], img.addr[i]));
}

void	drawwall_2(t_prog *cub3d, t_raycast *tmp, float x)
{
	int			y;
	u_int32_t	color;
	double		step;
	double		texpos;

	step = 5.0 * PXLS / tmp->lineHeight;
	texpos = (tmp->drawStart - SCREEN_H / 2
			+ tmp->lineHeight / 2) * step;
	y = tmp->drawStart;
	while (y < tmp->drawEnd)
	{
		tmp->texY = (int) texpos & (PXLS - 1);
		texpos += step;
		if (tmp->side == 0)
			color = gettexel(cub3d->we_text_img, tmp->texX, tmp->texY);
		else if (tmp->side == 1)
			color = gettexel(cub3d->ea_text_img, tmp->texX, tmp->texY);
		else if (tmp->side == 2)
			color = gettexel(cub3d->no_text_img, tmp->texX, tmp->texY);
		else if (tmp->side == 3)
			color = gettexel(cub3d->so_text_img, tmp->texX, tmp->texY);
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->drawStart, color);
		tmp->drawStart++;
		y++;
	}
}

// 0 = west, 1 = east, 2 = north, 3 = south
void	drawwall(t_prog *cub3d, t_raycast *tmp, float x)
{
	if (tmp->side == 0 || tmp->side == 1)
		tmp->wallX = cub3d->py + tmp->perpWallDist * tmp->rayDirY;
	else
		tmp->wallX = cub3d->px + tmp->perpWallDist * tmp->rayDirX;
	tmp->wallX -= floor((tmp->wallX));
	tmp->texX = (int)(tmp->wallX * (double) PXLS);
	if ((tmp->side == 0 || tmp->side == 1) && tmp->rayDirX > 0)
		tmp->texX = PXLS - tmp->texX - 1;
	if ((tmp->side == 2 || tmp->side == 3) && tmp->rayDirY < 0)
		tmp->texX = PXLS - tmp->texX - 1;
	drawwall_2(cub3d, tmp, x);
}

void	drawwalls(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	y;

	drawwall(cub3d, tmp, x);
	y = tmp->drawEnd;
	while (y <= SCREEN_H)
	{
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, y, cub3d->floor.hex_color);
		y++;
	}
	y = 0;
	while (y <= (SCREEN_H - tmp->lineHeight) / 2)
	{
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, y, cub3d->ceiling.hex_color);
		y++;
	}
}
