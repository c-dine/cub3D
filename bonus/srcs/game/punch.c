/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   punch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:57:20 by ntan              #+#    #+#             */
/*   Updated: 2022/05/30 11:11:54 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	weapons_select(t_prog *cub3d)
{
	if (cub3d->weapons == 0)
		punch(cub3d);
	else if (cub3d->weapons == 1)
		gun(cub3d);
}

void	transp_background(t_prog *cub3d, t_image *sprite)
{
	int	i;
	int	image_pos[2];
	int	xy[2];

	image_pos[0] = (cub3d->win_x - 600);
	image_pos[1] = (cub3d->win_y - 500);
	i = 0;
	while (i < sprite->size_x * sprite->size_y * 4)
	{
		xy[0] = image_pos[0] + (i % sprite->line_length) / 4;
		xy[1] = image_pos[1] + (i / sprite->line_length);
		if ((unsigned char)sprite->addr[i] == 87 && (unsigned char)
			sprite->addr[i + 1] == 217
			&& (unsigned char)sprite->addr[i + 2] == 126)
			;
		else
			mlx_pixel_put(cub3d->mlx, cub3d->win, xy[0], xy[1],
				getcolorrgb((signed char)sprite->addr[i + 2],
					(signed char)sprite->addr[i + 1],
					(signed char)sprite->addr[i]));
		i += 4;
	}
}

void	punch(t_prog *cub3d)
{
	static int	frame = 0;

	if (cub3d->punch_animation == 1)
	{
		if (frame < 6)
			transp_background(cub3d, &cub3d->punch1);
		else if (frame < 12)
			transp_background(cub3d, &cub3d->punch2);
		else if (frame < 18)
			transp_background(cub3d, &cub3d->punch3);
		frame++;
		if (frame >= 18)
		{
			cub3d->punch_animation = 0;
			frame = 0;
		}
	}
}

void	gun(t_prog *cub3d)
{
	static int	frame = 0;

	if (cub3d->punch_animation == 1)
	{
		if (frame < 4)
			transp_background(cub3d, &cub3d->gun1);
		else if (frame < 8)
			transp_background(cub3d, &cub3d->gun2);
		else if (frame < 12)
			transp_background(cub3d, &cub3d->gun3);
		else if (frame < 16)
			transp_background(cub3d, &cub3d->gun4);
		else if (frame < 20)
			transp_background(cub3d, &cub3d->gun5);
		frame++;
		if (frame >= 20)
		{
			cub3d->punch_animation = 0;
			frame = 0;
		}
	}
}
