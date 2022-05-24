/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:59:53 by cdine             #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	check_extremes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '\0')
			return (ERROR);
		i++;
	}
	return (NOERR);
}

void	check_elem_map_norm(t_prog *cub3d, int *tab, char **map)
{
	get_player_infos(cub3d, tab[0], tab[1], map[tab[0]][tab[1]]);
	map[tab[0]][tab[1]] = '0';
	tab[2]++;
}

int	check_elements_map(char **map, int line, t_prog *cub3d)
{
	int	tab[4];

	tab[0] = -1;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	while (map[++tab[0]])
	{
		tab[1] = -1;
		while (map[tab[0]][++tab[1]])
		{
			if (map[tab[0]][tab[1]] == 'W' || map[tab[0]][tab[1]] == 'E'
				|| map[tab[0]][tab[1]] == 'N' || map[tab[0]][tab[1]] == 'S')
				check_elem_map_norm(cub3d, tab, map);
			else if (map[tab[0]][tab[1]] == 'D')
				tab[3]++;
			else if (map[tab[0]][tab[1]] != '1' && map[tab[0]][tab[1]] != '0'
				&& map[tab[0]][tab[1]] != ' ' && map[tab[0]][tab[1]] != '2')
				return (map_error_msg(2),
					printf(" line %d\n", line + tab[0]), ERROR);
		}
	}
	if (tab[2] != 1 || tab[3] == 0)
		return (map_error_msg(1), ERROR);
	return (NOERR);
}

int	check_middle(int j, char **map, int line)
{
	int	i;

	if (map[j][0] != '1' || map[j][ft_strlen(map[j]) - 1] != '1')
		return (map_error_msg(0), printf(" line %d\n", line + j), ERROR);
	i = 0;
	while (map[j][i])
	{
		if (map[j][i] == '0' && (map[j][i - 1] == ' ' || map[j][i - 1] == '\0'
			|| map[j][i + 1] == ' ' || map[j][i + 1] == '\0'
			|| map[j - 1][i] == ' ' || map[j - 1][i] == '\0'
			|| map[j + 1][i] == ' ' || map[j + 1][i] == '\0'))
			return (map_error_msg(0), printf(" around line %d\n", line + j),
				ERROR);
		i++;
	}
	return (NOERR);
}

int	get_map(t_prog *cub3d, char **map, int line)
{
	int	i;

	replace_backslash_n(map);
	replace_spaces(map);
	if (check_elements_map(map, line, cub3d) == ERROR)
		return (ERROR);
	if (check_extremes(map[0]) == ERROR)
		return (map_error_msg(0), printf(" line %d\n", line), ERROR);
	i = 1;
	while (map[i + 1])
	{
		if (check_middle(i, map, line) == ERROR)
			return (ERROR);
		i++;
	}
	if (check_extremes(map[i]) == ERROR)
		return (map_error_msg(0), printf(" line %d\n", line + i), ERROR);
	cub3d->map = map;
	get_size_map(cub3d, map);
	return (NOERR);
}
