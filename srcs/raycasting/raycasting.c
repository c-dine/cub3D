/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:59:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/20 19:19:42 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	initvarray(t_prog *cub3d, t_raycast *tmp, float x)
{
	tmp->cameraX = 2 * x / (double) 150 - 1;
	tmp->rayDirX = cub3d->pdx + cub3d->planeX * tmp->cameraX;
	tmp->rayDirY = cub3d->pdy + cub3d->planeY * tmp->cameraX;
	tmp->mapX = (int) cub3d->px;
	tmp->mapY = (int) cub3d->py;
	if (tmp->rayDirX == 0)
		tmp->deltaDistX = 1e30;
	else
		tmp->deltaDistX = fabs(1 / tmp->rayDirX);
	if (tmp->rayDirY == 0)
		tmp->deltaDistY = 1e30;
	else
		tmp->deltaDistY = fabs(1 / tmp->rayDirY);
	tmp->hit = 0;
}

void	getsteps(t_prog *cub3d, t_raycast *tmp)
{
	if (tmp->rayDirX < 0)
	{
		tmp->stepX = -1;
		tmp->sideDistX = (cub3d->px - tmp->mapX) * tmp->deltaDistX;
	}
	else
	{
		tmp->stepX = 1;
		tmp->sideDistX = (tmp->mapX + 1.0 - cub3d->px) * tmp->deltaDistX;
	}
	if (tmp->rayDirY < 0)
	{
		tmp->stepY = -1;
		tmp->sideDistY = (cub3d->py - tmp->mapY) * tmp->deltaDistY;
	}
	else
	{
		tmp->stepY = 1;
		tmp->sideDistY = (tmp->mapY + 1.0 - cub3d->py) * tmp->deltaDistY;
	}
}

void	getwallhit(t_prog *cub3d, t_raycast *tmp)
{
	while (tmp->hit == 0)
	{
		if (tmp->sideDistX < tmp->sideDistY)
		{
			tmp->sideDistX += tmp->deltaDistX;
			tmp->mapX += tmp->stepX;
			if (tmp->mapX >= cub3d->px)
				tmp->side = 0;
			else
				tmp->side = 1;
		}
		else
		{
			tmp->sideDistY += tmp->deltaDistY;
			tmp->mapY += tmp->stepY;
			if (tmp->mapY > cub3d->py)
				tmp->side = 2;
			else
				tmp->side = 3;
		}
		if (cub3d->map[tmp->mapY / PXLS][tmp->mapX / PXLS] == '1')
		{
			mlx_pixel_put(cub3d->mlx, cub3d->win,
				tmp->mapX, tmp->mapY, 0xFF3333);
			tmp->hit = 1;
		}
	}
}

void	getwalldist(t_raycast *tmp)
{
	if (tmp->side == 0 || tmp->side == 1)
		tmp->perpWallDist = (tmp->sideDistX - tmp->deltaDistX);
	else
		tmp->perpWallDist = (tmp->sideDistY - tmp->deltaDistY);
	tmp->lineHeight = (int)(SCREEN_H / (tmp->perpWallDist));
	tmp->drawStart = -tmp->lineHeight / 2 + SCREEN_H / 2;
	if (tmp->drawStart < 0)
		tmp->drawStart = 0;
	tmp->drawEnd = tmp->lineHeight / 2 + SCREEN_H / 2;
	if (tmp->drawEnd >= SCREEN_H)
		tmp->drawEnd = SCREEN_H - 1;
}

int	raycasting(t_prog *cub3d)
{
	t_raycast	tmp;
	float		x;

	x = 0;
	while (x < 150)
	{
		initvarray(cub3d, &tmp, x);
		getsteps(cub3d, &tmp);
		getwallhit(cub3d, &tmp);
		getwalldist(&tmp);
		drawwalls(cub3d, &tmp, x);
		x += 0.10005;
	}
	return (NOERR);
}
