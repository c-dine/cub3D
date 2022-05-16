/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:10:34 by cdine             #+#    #+#             */
/*   Updated: 2022/05/16 15:59:45 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		get_wall_texture(t_prog *cub3d, char *line)
{
	int		i;
	int		fd;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = '\0';
	fd = open(&line[i], O_RDONLY);
	if (fd == -1)
		return (ERROR);
	close(fd);
	if (ft_strncmp(line, "NO ", 3) == 0)
		cub3d->no_text = line;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		cub3d->so_text = line;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		cub3d->we_text = line;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		cub3d->ea_text = line;
	return (NOERR);
}

int	put_rgb_color(t_prog *cub3d, char *line, int nb, int count)
{
	t_color	*tmp;

	if (nb < 0 || nb > 255)
		return (ERROR);
	if (ft_strncmp("F ", line, 2) == 0)
		tmp = &(cub3d->floor);
	else
		tmp = &(cub3d->ceiling);
	if (count == 0)
		tmp->r = nb;
	else if (count == 1)
		tmp->g = nb;
	else
		tmp->b = nb;
	return (NOERR);
}

int		get_f_c_texture(t_prog *cub3d, char *line)
{
	int	i;
	int	count;
	int	tmp;

	count = 0;
	i = 1;
	while (count < 3)
	{
		tmp = 0;
		while (line[i] == ' ')
			i++;
		while (line[i] >= '0' && line[i] <= '9')
			tmp	= tmp * 10 + line[i++] - '0';
		if ((line[i] != ',' && count < 2) || (line[i] != '\n' && count == 2) || put_rgb_color(cub3d, line, tmp, count) == ERROR)
			return (ERROR);
		count++;
		i++;
	}
	return (NOERR);
}
