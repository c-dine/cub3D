/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:42:21 by ntan              #+#    #+#             */
/*   Updated: 2022/05/21 18:11:26 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_corner_map(t_drawmap *tmp, t_prog *cub3d)
{
	tmp->x = floor(cub3d->px / PXLS) - 5;
	tmp->y = floor(cub3d->py / PXLS) - 4;
	if (tmp->x < 0)
		tmp->x = 0;
	if (tmp->y < 0)
		tmp->y = 0;
	tmp->tmp = tmp->x;
}

void	get_corner_pos_on_screen(t_prog *cub3d, t_drawmap *tmp)
{
	if (floor(cub3d->px / PXLS) - 5 < 0)
		tmp->x_map = 1040 + PXLS * (5 - floor(cub3d->px / PXLS));
	else
		tmp->x_map = 1040;
	if (floor(cub3d->py / PXLS) - 4 < 0)
		tmp->y_map = 16 + PXLS * (4 - floor(cub3d->py / PXLS));
	else
		tmp->y_map = 16;
}

int	draw_map(t_prog *cub3d)
{
	t_drawmap	tmp;

	get_corner_map(&tmp, cub3d);
	get_corner_pos_on_screen(cub3d, &tmp);
	tmp.xmap_tmp = tmp.x_map;
	while (cub3d->map[tmp.y] && tmp.y_map < 140)
	{
		tmp.x = tmp.tmp;
		tmp.x_map = tmp.xmap_tmp;
		while (cub3d->map[tmp.y][tmp.x] && tmp.x_map < 1248)
		{
			if (cub3d->map[tmp.y][tmp.x] == '1')
				mlx_put_image_to_window(cub3d->mlx, cub3d->win,
					cub3d->minimap_ext.image, tmp.x_map, tmp.y_map);
			else
				mlx_put_image_to_window(cub3d->mlx, cub3d->win,
					cub3d->minimap_int.image, tmp.x_map, tmp.y_map);
			tmp.x++;
			tmp.x_map += PXLS;
		}
		tmp.y++;
		tmp.y_map += PXLS;
	}
	return (1);
}

int	draw_player(t_prog *cub3d)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			mlx_pixel_put(cub3d->mlx, cub3d->win,
				1040 + 5 * PXLS + PXLS / 2 + j, 16 + 4 * PXLS + 5 + i, RED);
			j++;
		}
		i++;
	}
	k = 0;
	while (k < 5)
	{
		mlx_pixel_put(cub3d->mlx, cub3d->win, 1040 + 5 * PXLS + PXLS / 2 + 3
			+ cub3d->pdx * k, 16 + 4 * PXLS + 5 + 2 + cub3d->pdy * k, RED);
		k++;
	}
	return (0);
}
