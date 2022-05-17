/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:59:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/17 17:15:46 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

typedef struct s_raycast
{
	float	Tan;
	int		dof;
	int		side;
	int		disV; // distance from hit point vertical
	int		disH; // distance from hit point horizontal

	float	rx; // where ray hits first square
	float	ry;
	float	xo; // vector to add to rx to get to next square 
	float	yo;
	int		mx; // map hit position
	int		my;
	float	vx;
	float	vy;
}				t_raycast;


int	drawVertical(t_prog *cub3d, float ra, t_raycast *tmp)
{
	tmp->dof = 0;
	tmp->side = 0;
	tmp->disV = 100000;
	tmp->Tan = tan(degToRad(ra));
	
	if (cos(degToRad(ra)) > 0.001)
	{
		tmp->rx = (((int) cub3d->px / PXLS) * PXLS ) + PXLS;
		tmp->ry = (cub3d->px - tmp->rx) * tmp->Tan + cub3d->py;
		tmp->xo = PXLS;
		tmp->yo = - tmp->xo * tmp->Tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
	{
		tmp->rx = (((int) cub3d->px / PXLS) * PXLS ) - 0.0001;
		tmp->ry = (cub3d->px - tmp->rx) * tmp->Tan + cub3d->py;
		tmp->xo = - PXLS;
		tmp->yo = - tmp->xo * tmp->Tan;
	}
	else
	{
		tmp->rx = cub3d->px;
		tmp->ry = cub3d->py;
		tmp->dof = sqrt(PXLS);
	}
	
	while (tmp->dof < sqrt(PXLS))
	{
		tmp->mx = (int) (tmp->rx) / PXLS;
		tmp->my = (int) (tmp->ry) / PXLS;
		if (tmp->mx < cub3d->map_x && tmp->mx > 0 && tmp->mx < cub3d->map_x
			&& tmp->my < cub3d->map_y && tmp->my > 0
			&& cub3d->map2[tmp->my][tmp->mx] == '1')
		{
			tmp->dof = sqrt(PXLS);
			tmp->disV = cos(degToRad(ra)) * (tmp->rx - cub3d->px) - sin(degToRad(ra))*(tmp->ry - cub3d->py);
			mlx_pixel_put(cub3d->mlx, cub3d->win, tmp->rx, tmp->ry, 0xFF3333);
		}
		else
		{
			tmp->rx += tmp->xo;
			tmp->ry += tmp->yo;
			tmp->dof++;
		}
	}
	tmp->vx = tmp->rx;
	tmp->vy = tmp->vy;
	return (NOERR);
}

int	drawHorizontal(t_prog *cub3d, float ra, t_raycast *tmp)
{
	tmp->dof = 0;
	tmp->disH = 100000;
	tmp->Tan = 1.0 / tmp->Tan;
	
    if (sin(degToRad(ra)) > 0.001)
	{
		tmp->ry = (((int) cub3d->py / PXLS ) * PXLS) - 0.0001;
		tmp->rx=(cub3d->py - tmp->ry) * tmp->Tan + cub3d->px;
		tmp->yo= - PXLS;
		tmp->xo= - tmp->yo * tmp->Tan;
	}
	else if (sin(degToRad(ra)) < -0.001)
	{
		tmp->ry=(((int)cub3d->py / PXLS) * PXLS) + 64;
		tmp->rx=(cub3d->py - tmp->ry) * tmp->Tan + cub3d->px;
		tmp->yo = PXLS; 
		tmp->xo= - tmp->yo * tmp->Tan;
	}
	else
	{
		tmp->rx=cub3d->px;
		tmp->ry=cub3d->py;
		tmp->dof=sqrt(PXLS);
	}
	while(tmp->dof<sqrt(PXLS)) 
	{ 
		tmp->mx = (int)(tmp->rx) / PXLS;
		tmp->my= (int)(tmp->ry) / PXLS;
		if (tmp->mx < cub3d->map_x && tmp->mx > 0 && tmp->mx < cub3d->map_x
			&& tmp->my < cub3d->map_y && tmp->my > 0
			&& cub3d->map2[tmp->my][tmp->mx] == '1')
		{
			tmp->dof=sqrt(PXLS); 
			tmp->disH=cos(degToRad(ra))*(tmp->rx-cub3d->px) - sin(degToRad(ra))*(tmp->ry-cub3d->py);
			mlx_pixel_put(cub3d->mlx, cub3d->win, tmp->rx, tmp->ry, 0xFF3333);
		}         
		else
		{
			tmp->rx += tmp->xo;
			tmp->ry += tmp->yo;
			tmp->dof += 1;
		}
	} 
	return (NOERR);
}

int	drawRays(t_prog *cub3d)
{
	float	ra;
	int		nb_rays;
	t_raycast	tmp;

	nb_rays = 0;
	ra = fixAngle(cub3d->pa + 90);
	while (nb_rays < 1)
	{
		drawVertical(cub3d, ra, &tmp);
		drawHorizontal(cub3d, ra, &tmp);
		ra = fixAngle(ra - 1);
		nb_rays++;
	}
	return (NOERR);
}