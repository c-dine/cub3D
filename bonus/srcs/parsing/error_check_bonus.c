/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:36:55 by cdine             #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	print_msg_check_error(int i)
{
	printf("Error\nWrong instructions format: ");
	printf("instruction not recognized, line %d\n", i + 1);
}

int	check_error_2(t_prog *cub3d)
{
	if (check_presence_all_instructions(cub3d) == ERROR)
		return (ERROR);
	get_doors(cub3d);
	return (NOERR);
}

int	check_error(char **file, t_prog *cub3d)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	while (file[++i])
	{
		j = 0;
		while (file[i][j] && (file[i][j] == ' ' || file[i][j] == '	'))
			j++;
		ret = check_text_f_c(cub3d, &file[i][j], i);
		if (ret == ERROR)
			return (ERROR);
		else if (file[i][0] == '1')
		{
			if (get_map(cub3d, &file[i], i + 1) == ERROR)
				return (ERROR);
			break ;
		}
		else if (file[i][j] != '\n' && ret != 2)
			return (print_msg_check_error(i), ERROR);
	}
	if (check_error_2(cub3d) == ERROR)
		return (ERROR);
	return (NOERR);
}
