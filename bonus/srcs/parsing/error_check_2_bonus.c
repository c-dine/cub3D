/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:22:09 by ntan              #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	ft_checkextension(char *file)
{
	int	i;

	if (ft_strlen(file) < 5)
		return (ERROR);
	i = ft_strlen(file) - 4;
	if (file[i] == '.' && file[i + 1] == 'c' && file[i + 2] == 'u'
		&& file[i + 3] == 'b' && file[i - 1] != '/')
		return (NOERR);
	else
		return (ERROR);
}

int	check_presence_all_instructions(t_prog *cub3d)
{
	if (cub3d->ceiling.b == -1 || cub3d->floor.b == -1 || cub3d->no_text == NULL
		|| cub3d->ea_text == NULL || cub3d->we_text == NULL
		|| cub3d->so_text == NULL)
		printf("Error\n");
	if (cub3d->ceiling.b == -1)
		printf("Ceiling color instruction missing\n");
	if (cub3d->floor.b == -1)
		printf("Floor color instruction missing\n");
	if (cub3d->no_text == NULL)
		printf("North texture instruction missing\n");
	if (cub3d->ea_text == NULL)
		printf("East texture instruction missing\n");
	if (cub3d->we_text == NULL)
		printf("West texture instruction missing\n");
	if (cub3d->so_text == NULL)
		printf("South texture instruction missing\n");
	if (cub3d->ceiling.b == -1 || cub3d->floor.b == -1 || cub3d->no_text == NULL
		|| cub3d->ea_text == NULL || cub3d->we_text == NULL
		|| cub3d->so_text == NULL)
		return (ERROR);
	return (NOERR);
}

int	check_text_f_c(t_prog *cub3d, char *file, int i)
{
	if (ft_strncmp(file, "NO ", 3) == 0 || ft_strncmp(file, "SO ", 3) == 0
		|| ft_strncmp(file, "WE ", 3) == 0
		|| ft_strncmp(file, "EA ", 3) == 0)
	{
		if (get_wall_texture(cub3d, file) == ERROR)
			return (printf("Error\nWrong instructions format: wall "),
				printf("texture, line %d\n", i + 1), ERROR);
		return (2);
	}
	else if (ft_strncmp(file, "F ", 2) == 0 || ft_strncmp(file, "C ", 2) == 0)
	{
		if (get_f_c_texture(cub3d, file) == ERROR)
			return (printf("Error\nWrong instructions format: floor and "),
				printf("ceiling color, line %d\n", i + 1), ERROR);
		return (2);
	}
	return (NOERR);
}
