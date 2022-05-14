/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:59:45 by ntan              #+#    #+#             */
/*   Updated: 2022/05/14 16:58:40 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(char *str, int size)
{
	int		i;
	char	*res;

	res = malloc(size);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*gnl(int fd)
{
	char		save[999999];
	char		buf[1];
	char		*res;
	static int	rd;
	int			i;

	i = 0;
	if (rd < 0 || fd < 0)
		return (NULL);
	while (1)
	{
		rd = read(fd, buf, 1);
		if (rd == 0)
			break ;
		save[i] = buf[0];
		i++;
		if (buf[0] == '\n')
			break ;
	}
	save[i] = '\0';
	res = ft_strdup(save, i);
	if (rd == 0)
		rd = -1;
	return (res);
}
