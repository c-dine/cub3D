/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:43:37 by cdine             #+#    #+#             */
/*   Updated: 2022/05/24 15:23:00 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	open_door(t_door *door, t_prog *cub3d)
{	
	if (door->frame < 10)
		door->door_state = 1;
	else if (door->frame < 20)
		door->door_state = 2;
	else if (door->frame < 30)
		door->door_state = 3;
	else if (door->frame < 40)
		door->door_state = 4;
	else if (door->frame < 50)
		door->door_state = 5;
	else if (door->frame < 60)
		door->door_state = 6;
	door->frame++;
	if (door->frame >= 60)
	{
		cub3d->map[door->y][door->x] = '3';
		door->frame = 0;
		door->is_closing = 0;
		door->is_closed = 0;
	}
}

void	close_door(t_door *door, t_prog *cub3d)
{
		cub3d->map[door->y][door->x] = '2';
		if (door->frame < 10)
			door->door_state = 6;
		else if (door->frame < 20)
			door->door_state = 5;
		else if (door->frame < 30)
			door->door_state = 4;
		else if (door->frame < 40)
			door->door_state = 3;
		else if (door->frame < 50)
			door->door_state = 2;
		else if (door->frame < 60)
			door->door_state = 1;
		door->frame++;
		if (door->frame >= 60)
		{
			door->frame = 0;
			door->is_closing = 0;
			door->is_closed = 1;
		}
}

void	door_animation(t_prog *cub3d)
{
	t_list	*tmp;

	tmp = cub3d->doors->next;
	while (tmp)
	{
		if (tmp->content->is_closing == 1)
			close_door(tmp->content, cub3d);
		else if (tmp->content->is_closing == 2)
			open_door(tmp->content, cub3d);
		tmp = tmp->next;
	}
}

t_door	*get_door(t_prog *cub3d)
{
	t_list	*tmp;

	tmp = cub3d->doors->next;
	while (tmp)
	{
		if ((int) (cub3d->px / PXLS + cub3d->pdx * 4 / PXLS) == tmp->content->x && (int) (cub3d->py / PXLS + cub3d->pdy * 4 / PXLS) == tmp->content->y)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_door	*get_door_with_xy(t_prog *cub3d, int x, int y)
{
	t_list	*tmp;

	tmp = cub3d->doors->next;
	while (tmp)
	{
		if (tmp->content->x == x && tmp->content->y == y)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}