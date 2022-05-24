/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:59:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	initvarray(t_prog *cub3d, t_raycast *tmp, float x)
{
	tmp->camera_x = 2 * x / (double) 150 - 1;
	tmp->ray_dir_x = cub3d->pdx + cub3d->plane_x * tmp->camera_x;
	tmp->ray_dir_y = cub3d->pdy + cub3d->plane_y * tmp->camera_x;
	tmp->map_x = (int) cub3d->px;
	tmp->map_y = (int) cub3d->py;
	if (tmp->ray_dir_x == 0)
		tmp->delta_dist_x = 1e30;
	else
		tmp->delta_dist_x = fabs(1 / tmp->ray_dir_x);
	if (tmp->ray_dir_y == 0)
		tmp->delta_dist_y = 1e30;
	else
		tmp->delta_dist_y = fabs(1 / tmp->ray_dir_y);
	tmp->hit = 0;
}

void	getsteps(t_prog *cub3d, t_raycast *tmp)
{
	if (tmp->ray_dir_x < 0)
	{
		tmp->step_x = -1;
		tmp->side_dist_x = (cub3d->px - tmp->map_x) * tmp->delta_dist_x;
	}
	else
	{
		tmp->step_x = 1;
		tmp->side_dist_x = (tmp->map_x + 1.0 - cub3d->px) * tmp->delta_dist_x;
	}
	if (tmp->ray_dir_y < 0)
	{
		tmp->step_y = -1;
		tmp->side_dist_y = (cub3d->py - tmp->map_y) * tmp->delta_dist_y;
	}
	else
	{
		tmp->step_y = 1;
		tmp->side_dist_y = (tmp->map_y + 1.0 - cub3d->py) * tmp->delta_dist_y;
	}
}

void	getwalldist(t_raycast *tmp)
{
	if (tmp->side == 0 || tmp->side == 1)
		tmp->perp_wall_dist = (tmp->side_dist_x - tmp->delta_dist_x);
	else
		tmp->perp_wall_dist = (tmp->side_dist_y - tmp->delta_dist_y);
	tmp->line_height = (int)(SCREEN_H / (tmp->perp_wall_dist));
	tmp->draw_start = -tmp->line_height / 2 + SCREEN_H / 2;
	if (tmp->draw_start < 0)
		tmp->draw_start = 0;
	tmp->draw_end = tmp->line_height / 2 + SCREEN_H / 2;
	if (tmp->draw_end >= SCREEN_H)
		tmp->draw_end = SCREEN_H - 1;
}

void	getwallhit(t_prog *cub3d, t_raycast *tmp)
{
	while (tmp->hit == 0)
	{
		if (tmp->side_dist_x < tmp->side_dist_y)
		{
			tmp->side_dist_x += tmp->delta_dist_x;
			tmp->map_x += tmp->step_x;
			if (tmp->map_x >= cub3d->px)
				tmp->side = 0;
			else
				tmp->side = 1;
		}
		else
		{
			tmp->side_dist_y += tmp->delta_dist_y;
			tmp->map_y += tmp->step_y;
			if (tmp->map_y > cub3d->py)
				tmp->side = 2;
			else
				tmp->side = 3;
		}
		if (cub3d->map[tmp->map_y / PXLS][tmp->map_x / PXLS] == '1'
			|| cub3d->map[tmp->map_y / PXLS][tmp->map_x / PXLS] == '2'
			|| cub3d->map[tmp->map_y / PXLS][tmp->map_x / PXLS] == 'D')
			tmp->hit = 1;
	}
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
