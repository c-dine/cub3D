/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:42:21 by ntan              #+#    #+#             */
/*   Updated: 2022/05/20 18:04:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	draw_map(t_prog *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->map_y)
	{
		x = 0;
		while (x < ft_strlen(cub3d->map[y]))
		{
			if (cub3d->map[y][x] == '1')
				mlx_put_image_to_window(cub3d->mlx, cub3d->win,
					cub3d->minimap_ext.image, x * PXLS, y * PXLS);
			else
				mlx_put_image_to_window(cub3d->mlx, cub3d->win,
					cub3d->minimap_int.image, x * PXLS, y * PXLS);
			x++;
		}
		y++;
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
				cub3d->px + j, cub3d->py + i, RED);
			j++;
		}
		i++;
	}
	k = 0;
	while (k < 5)
	{
		mlx_pixel_put(cub3d->mlx, cub3d->win, cub3d->px
			+ cub3d->pdx * k, cub3d->py + cub3d->pdy * k, RED);
		k++;
	}
	return (0);
}
