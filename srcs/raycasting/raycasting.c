/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:59:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/17 20:42:46 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

typedef struct s_raycast
{
	// float	Tan;
	// int		dof;
	// int		side;
	// int		disV; // distance from hit point vertical
	// int		disH; // distance from hit point horizontal

	// float	rx; // where ray hits first square
	// float	ry;
	// float	xo; // vector to add to rx to get to next square 
	// float	yo;
	// int		mx; // map hit position
	// int		my;
	// float	vx;
	// float	vy;


	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int 	mapX;
	int 	mapY;
	//length of ray from current position to next x or y-side
	double 	sideDistX;
	double 	sideDistY;
	//length of ray from one x or y-side to next x or y-side
	double	 deltaDistX;
	double	 deltaDistY;
	double	 perpWallDist;
	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
}				t_raycast;


int	drawRays(t_prog *cub3d)
{
	t_raycast	tmp;
	int			x;

	x = 0;
	while (x < cub3d->map_x)
	{
		// calcul direction du ray
		tmp.cameraX = 2 * x / (double) cub3d->map_x - 1;
		tmp.rayDirX = cub3d->pdx + cub3d->planeX * tmp.cameraX;
		tmp.rayDirY = cub3d->pdy + cub3d->planeY * tmp.cameraX;
		
		// init
		tmp.mapX = (int) cub3d->px;
		tmp.mapY = (int) cub3d->py;
		if (tmp.rayDirX == 0)
			tmp.deltaDistX = 1e30;
		else
			tmp.deltaDistX = fabs(1 / tmp.rayDirX);
		if (tmp.rayDirY == 0)
			tmp.deltaDistY = 1e30;
		else
			tmp.deltaDistY = fabs(1 / tmp.rayDirY);
		tmp.hit = 0;

		// calcul du step entre chaque case
		if (tmp.rayDirX < 0)
		{
			tmp.stepX = -1;
			tmp.sideDistX = (cub3d->px - tmp.mapX) * tmp.deltaDistX;
		}
		else
		{
			tmp.stepX = 1;
			tmp.sideDistX = (tmp.mapX + 1.0 - cub3d->px) * tmp.deltaDistX;
		}
		if (tmp.rayDirY < 0)
		{
			tmp.stepY = -1;
			tmp.sideDistY = (cub3d->py - tmp.mapY) * tmp.deltaDistY;
		}
		else
		{
			tmp.stepY = 1;
			tmp.sideDistY = (tmp.mapY + 1.0 - cub3d->py) * tmp.deltaDistY;
		}
		
		// trouver premiere collision a un mur
		while (tmp.hit == 0)
		{
			if (tmp.sideDistX < tmp.sideDistY)
			{
				tmp.sideDistX += tmp.deltaDistX;
				tmp.mapX += tmp.stepX;
				tmp.side = 0;
			}
			else
			{
				tmp.sideDistY += tmp.deltaDistY;
				tmp.mapY += tmp.stepY;
				tmp.side = 1;
			}
			printf("%d %d\n", tmp.mapX / PXLS, tmp.mapY / PXLS);
			//Check if ray has hit a wall
			if (cub3d->map2[tmp.mapY / PXLS][tmp.mapX / PXLS] == '1')
			{
				mlx_pixel_put(cub3d->mlx, cub3d->win, tmp.mapX, tmp.mapY, 0xFF3333); 
				tmp.hit = 1;
			}
		}
		
		// calcul distance du mur
		if (tmp.side == 0) 
			tmp.perpWallDist = (tmp.sideDistX - tmp.deltaDistX);
    	else
		    tmp.perpWallDist = (tmp.sideDistY - tmp.deltaDistY);
		
		x++;
	}
	return (NOERR);
}