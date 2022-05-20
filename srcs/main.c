/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:47:26 by ntan              #+#    #+#             */
/*   Updated: 2022/05/20 20:08:35 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int ac, char **av)
{
	t_prog	cub3d;
	char	**file;

	if (ac != 2 || (ac == 2 && av[0][0] == '\0'))
		return (printf("Error\nPlease enter the pathway to a .cub map\n"), 1);
	file = get_file_content(av[1]);
	if (!file)
		return (1);
	init_prog(&cub3d);
	if (check_error(file, &cub3d) == ERROR)
		return (memrelease(), 1);
	game_loop(&cub3d);
	memrelease();
	return (0);
}
