/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:42:21 by ntan              #+#    #+#             */
/*   Updated: 2022/05/21 17:58:29 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	get_corner_map(int *x, int *y, int *tmp, t_prog *cub3d)
{
	*x = floor(cub3d->px / PXLS) - 5;
	*y = floor(cub3d->py / PXLS) - 4;
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	*tmp = *x;
}

void	get_corner_pos_on_screen(t_prog *cub3d, int *x_map, int *y_map)
{
	if (floor(cub3d->px / PXLS) - 5 < 0)
		*x_map = 1040 + PXLS * (5 - floor(cub3d->px / PXLS));
	if (floor(cub3d->py / PXLS) - 4 < 0)
		*y_map = 16 + PXLS * (4 - floor(cub3d->py / PXLS));
}

int	draw_map(t_prog *cub3d)
{
	int	x;
	int	y;
	int	x_map;
	int	y_map;
	int	tmp;
	int	xmap_tmp;

	x_map = 1040;
	y_map = 16;
	get_corner_map(&x, &y, &tmp, cub3d);
	get_corner_pos_on_screen(cub3d, &x_map, &y_map);
	xmap_tmp = x_map;
	while (cub3d->map[y] && y_map < 140)
	{
		x = tmp;
		x_map = xmap_tmp;
		while (cub3d->map[y][x] && x_map < 1248)
		{
			if (cub3d->map[y][x] == '1')
				mlx_put_image_to_window(cub3d->mlx, cub3d->win,
					cub3d->minimap_ext.image, x_map, y_map);
			else
			{
				mlx_put_image_to_window(cub3d->mlx, cub3d->win,
					cub3d->minimap_int.image, x_map, y_map);
			}
			x++;
			x_map += PXLS;
		}
		y++;
		y_map += PXLS;
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
