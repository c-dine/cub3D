/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:12:25 by cdine             #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	count_line_file(int fd)
{
	int	count;

	count = 0;
	while (gnl(fd))
		count++;
	return (count);
}

void	put_file_in_tab(int fd, char **res)
{
	char	*line;
	int		i;

	i = 0;
	line = gnl(fd);
	while (line)
	{
		res[i] = line;
		line = gnl(fd);
		i++;
	}
	res[i] = NULL;
}

char	**get_file_content(char *map)
{
	int		fd;
	char	**res;

	res = NULL;
	if (ft_checkextension(map) == ERROR)
		return (printf("Error\nPlease enter the pathway to a"),
			printf(" .cub map (extension error)\n"), NULL);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nPlease enter a valid pathway"),
			printf(" to a .cub map\n"), NULL);
	mempush(&res, sizeof(char *), count_line_file(fd) + 1);
	close(fd);
	fd = open(map, O_RDONLY);
	put_file_in_tab(fd, res);
	close(fd);
	return (res);
}

void	init_prog2(t_prog *cub3d)
{
	cub3d->tmp_img.image = NULL;
	cub3d->minimap_ext.image = NULL;
	cub3d->minimap_door.image = NULL;
	cub3d->minimap_int.image = NULL;
	cub3d->no_text_img.image = NULL;
	cub3d->so_text_img.image = NULL;
	cub3d->we_text_img.image = NULL;
	cub3d->ea_text_img.image = NULL;
	cub3d->door1.image = NULL;
	cub3d->door2.image = NULL;
	cub3d->door3.image = NULL;
	cub3d->door4.image = NULL;
	cub3d->door5.image = NULL;
	cub3d->door6.image = NULL;
	cub3d->win = NULL;
}

void	init_prog(t_prog *cub3d)
{
	cub3d->map = NULL;
	cub3d->no_text = NULL;
	cub3d->so_text = NULL;
	cub3d->we_text = NULL;
	cub3d->ea_text = NULL;
	cub3d->floor.r = -1;
	cub3d->floor.g = -1;
	cub3d->floor.b = -1;
	cub3d->floor.hex_color = 0;
	cub3d->ceiling.r = -1;
	cub3d->ceiling.g = -1;
	cub3d->ceiling.b = -1;
	cub3d->ceiling.hex_color = 0;
	init_prog2(cub3d);
}
