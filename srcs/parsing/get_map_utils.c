/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:58:41 by cdine             #+#    #+#             */
/*   Updated: 2022/05/20 19:59:45 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	map_error_msg(int type)
{
	printf("Error\nWrong instructions format: ");
	if (type == 0)
		printf("Map not closed");
	else if (type == 1)
		printf("More than one starting point for player\n");
	else if (type == 2)
		printf("Element not recognized in map");
}

void	get_player_infos(t_prog *cub3d, int i, int j, char c)
{
	cub3d->px = j * PXLS;
	cub3d->py = i * PXLS;
	if (c == 'N')
		cub3d->pa = PI + PI / 2;
	else if (c == 'S')
		cub3d->pa = PI / 2;
	else if (c == 'W')
		cub3d->pa = PI;
	else if (c == 'E')
		cub3d->pa = 0;
}

void	replace_backslash_n(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
			{
				map[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
}

void	replace_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	get_size_map(t_prog *cub3d, char **map)
{
	int	x;
	int	y;
	int	tmp;

	tmp = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > tmp)
			tmp = x;
		y++;
	}
	cub3d->map_x = x;
	cub3d->map_y = y;
}
