/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:34:27 by cdine             #+#    #+#             */
/*   Updated: 2022/05/20 19:04:46 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	newimage(t_prog *cub3d)
{
	cub3d->tmp_img.image = mlx_new_image(cub3d->mlx, SCREEN_W, SCREEN_H);
	cub3d->tmp_img.addr = mlx_get_data_addr
		(cub3d->tmp_img.image, &(cub3d->tmp_img.bits_per_pixel),
			&(cub3d->tmp_img.line_length), &(cub3d->tmp_img.endian));
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x < SCREEN_W && y < SCREEN_H && x > 0 && y > 0)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	getcolorrgb(int r, int g, int b)
{
	return (256 * 256 * r + 256 * g + b);
}

int	getcolortrgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
