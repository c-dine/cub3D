/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:05:53 by cdine             #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

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

t_image	*door_state(int state, t_prog *cub3d)
{
	if (state == 1)
		return (&cub3d->door1);
	else if (state == 2)
		return (&cub3d->door2);
	else if (state == 3)
		return (&cub3d->door3);
	else if (state == 4)
		return (&cub3d->door4);
	else if (state == 5)
		return (&cub3d->door5);
	else if (state == 6)
		return (&cub3d->door6);
	return (&cub3d->door1);
}
