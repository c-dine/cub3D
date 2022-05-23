/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:58:17 by cdine             #+#    #+#             */
/*   Updated: 2022/05/23 21:43:00 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_door	*add_door(int id, int x, int y)
{
	t_door *tmp;

	tmp = NULL;
	mempush(&tmp, sizeof(t_door), 1);
	tmp->id = id;
	tmp->x = x;
	tmp->y = y;
	tmp->door_state = 1;
	tmp->is_closing = 0;
	tmp->is_closed = 1;
	tmp->dist = -1;
	tmp->frame = 0;
	return (tmp);
}

t_list	*get_doors(t_prog *cub3d)
{
	int	i;
	int	j;
	int id;
	t_list	*tmp;

	id = 0;
	cub3d->doors = ft_lstnew(NULL);
	tmp = cub3d->doors;
	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j])
		{
			if (cub3d->map[i][j] == '2')
			{
				ft_lstadd_back(&tmp, ft_lstnew(add_door(id, j, i)));
				id++;
			}
			j++;
		}
		i++;	
	}

	// tmp = cub3d->doors->next;
	// while (tmp->next)
	// {
	// 	printf("OK %d\n", tmp->content->id);
	// 	tmp = tmp->next;
	// }
	// printf("OK %d\n", tmp->content->id);
	return (tmp);
}