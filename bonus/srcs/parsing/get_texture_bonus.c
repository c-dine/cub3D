/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:10:34 by cdine             #+#    #+#             */
/*   Updated: 2022/05/20 18:56:44 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_xpm_extension(char *line)
{
	int	i;

	if (ft_strlen(line) < 5)
		return (ERROR);
	i = ft_strlen(line) - 4;
	if (line[i] == '.' && line[i + 1] == 'x' && line[i + 2] == 'p'
		&& line[i + 3] == 'm' && line[i - 1] != '/')
		return (NOERR);
	else
		return (ERROR);
}

int	get_wall_texture(t_prog *cub3d, char *line)
{
	int			i;
	int			fd;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = '\0';
	fd = open(&line[i], O_RDONLY);
	if (fd == -1)
		return (ERROR);
	close(fd);
	if (check_xpm_extension(&line[i]) == ERROR)
		return (ERROR);
	if (ft_strncmp(line, "NO ", 3) == 0)
		cub3d->no_text = &line[i];
	else if (ft_strncmp(line, "SO ", 3) == 0)
		cub3d->so_text = &line[i];
	else if (ft_strncmp(line, "WE ", 3) == 0)
		cub3d->we_text = &line[i];
	else if (ft_strncmp(line, "EA ", 3) == 0)
		cub3d->ea_text = &line[i];
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
	{
		tmp->r = nb;
		tmp->hex_color += 256 * 256 * nb;
	}
	else if (count == 1)
	{
		tmp->g = nb;
		tmp->hex_color += 256 * nb;
	}
	else
	{
		tmp->b = nb;
		tmp->hex_color += nb;
	}
	return (NOERR);
}

void	get_f_c_texture2(char *line, int *i, int *tmp, int *check_error)
{
	*check_error = 0;
	*tmp = 0;
	while (line[*i] == ' ')
		(*i)++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		*check_error = 1;
		*tmp = *tmp * 10 + line[(*i)++] - '0';
	}
	while (line[*i] == ' ')
		(*i)++;
}

int	get_f_c_texture(t_prog *cub3d, char *line)
{
	int	i;
	int	count;
	int	tmp;
	int	check_error;

	count = 0;
	i = 1;
	while (count < 3)
	{
		get_f_c_texture2(line, &i, &tmp, &check_error);
		if ((line[i] != ',' && count < 2) || (line[i] != '\n' && count == 2)
			|| check_error == 0 || put_rgb_color(cub3d, line, tmp, count)
			== ERROR)
			return (ERROR);
		count++;
		i++;
	}
	if (count != 3)
		return (ERROR);
	return (NOERR);
}
