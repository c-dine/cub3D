/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/21 13:48:24 by cdine            ###   ########.fr       */
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

	step = 5.0 * PXLS / tmp->line_height;
	texpos = (tmp->draw_start - SCREEN_H / 2
			+ tmp->line_height / 2) * step;
	y = tmp->draw_start;
	while (y < tmp->draw_end)
	{
		tmp->tex_y = (int) texpos & (PXLS - 1);
		texpos += step;
		if (tmp->side == 0)
			color = gettexel(cub3d->we_text_img, tmp->tex_x, tmp->tex_y);
		else if (tmp->side == 1)
			color = gettexel(cub3d->ea_text_img, tmp->tex_x, tmp->tex_y);
		else if (tmp->side == 2)
			color = gettexel(cub3d->no_text_img, tmp->tex_x, tmp->tex_y);
		else if (tmp->side == 3)
			color = gettexel(cub3d->so_text_img, tmp->tex_x, tmp->tex_y);
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, tmp->draw_start, color);
		tmp->draw_start++;
		y++;
	}
}

// 0 = west, 1 = east, 2 = north, 3 = south
void	drawwall(t_prog *cub3d, t_raycast *tmp, float x)
{
	if (tmp->side == 0 || tmp->side == 1)
		tmp->wall_x = cub3d->py + tmp->perp_wall_dist * tmp->ray_dir_y;
	else
		tmp->wall_x = cub3d->px + tmp->perp_wall_dist * tmp->ray_dir_x;
	tmp->wall_x -= floor((tmp->wall_x));
	tmp->tex_x = (int)(tmp->wall_x * (double) PXLS);
	if ((tmp->side == 0 || tmp->side == 1) && tmp->ray_dir_x > 0)
		tmp->tex_x = PXLS - tmp->tex_x - 1;
	if ((tmp->side == 2 || tmp->side == 3) && tmp->ray_dir_y < 0)
		tmp->tex_x = PXLS - tmp->tex_x - 1;
	drawwall_2(cub3d, tmp, x);
}

void	drawwalls(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	y;

	drawwall(cub3d, tmp, x);
	y = tmp->draw_end;
	while (y <= SCREEN_H)
	{
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, y, cub3d->floor.hex_color);
		y++;
	}
	y = 0;
	while (y <= (SCREEN_H - tmp->line_height) / 2)
	{
		my_mlx_pixel_put(&cub3d->tmp_img, x * 10, y, cub3d->ceiling.hex_color);
		y++;
	}
}
