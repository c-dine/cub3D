/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/19 17:41:01 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	drawWalls(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	i = 0;
	while (i < tmp->lineHeight)
	{
		if (tmp->side == 0)
			my_mlx_pixel_put(&cub3d->tmp_img, x * 160, tmp->drawStart, RED);
		else if (tmp->side == 1)
			my_mlx_pixel_put(&cub3d->tmp_img, x * 160, tmp->drawStart, BLUE);
		else if (tmp->side == 2)
			my_mlx_pixel_put(&cub3d->tmp_img, x * 160, tmp->drawStart, GREEN);
		else
			my_mlx_pixel_put(&cub3d->tmp_img, x * 160, tmp->drawStart, YELLOW);
		tmp->drawStart++;
		i++;
	}
}
