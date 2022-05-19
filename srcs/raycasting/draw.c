/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:46:09 by cdine             #+#    #+#             */
/*   Updated: 2022/05/19 11:50:34 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	drawWalls(t_prog *cub3d, t_raycast *tmp, float x)
{
	int	i = 0;
	while (i < tmp->lineHeight)
	{
		if (tmp->side == 0)
			mlx_pixel_put(cub3d->mlx, cub3d->win, x * 160, tmp->drawStart, 0xFF3333);
		else
			mlx_pixel_put(cub3d->mlx, cub3d->win, x * 160, tmp->drawStart, 0x3734eb);
		tmp->drawStart++;
		i++;
	}
}
