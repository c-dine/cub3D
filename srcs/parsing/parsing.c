/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:12:25 by cdine             #+#    #+#             */
/*   Updated: 2022/05/19 19:10:40 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		return (printf("Error\nPlease enter the pathway to a .cub map (extension error)\n"), NULL);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nPlease enter a valid pathway to a .cub map\n"), NULL);
	mempush(&res, sizeof(char *), count_line_file(fd) + 1);
	close(fd);
	fd = open(map, O_RDONLY);
	put_file_in_tab(fd, res);
	close(fd);
	return (res);
}

void	init_prog(t_prog *cub3d)
{
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

	cub3d->tmp_img.image = NULL;
}
