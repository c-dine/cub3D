/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:59:45 by ntan              #+#    #+#             */
/*   Updated: 2022/05/24 18:55:57 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

static char	*ft_cattoline(char *buff, char *line)
{
	int			i;
	int			j;
	char		*new;

	mempush(&new, sizeof(char), ft_strlen(line) + ft_strlen(buff) + 1);
	if (new == NULL)
		exit(0);
	j = 0;
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	memfree(&line);
	while (buff[j] && buff[j] != '\n' && j < 100)
		new[i++] = buff[j++];
	if (buff[j] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

static void	ft_trim(char *buff, int ret, int checkfd)
{
	int	i;
	int	j;

	if (ret < 100 && ft_isline(buff) == 0 && checkfd == 1)
		buff[0] = '\0';
	else if (checkfd == 1)
	{
		i = 0;
		j = 0;
		while ((buff[i] != '\n' && i < 100))
			i++;
		i++;
		while (buff[i])
			buff[j++] = buff[i++];
		buff[j] = '\0';
	}
}

static int	ft_checkfd(int fd, int ret)
{
	if (fd == -1)
		return (0);
	if (ret == -1)
		return (0);
	return (1);
}

void	ft_ret_val(char *buff, int fd, int *ret)
{
	if (ft_strlen(buff) == 0)
		*ret = read(fd, buff, 100);
	else
		*ret = 100;
}

char	*gnl(int fd)
{
	char			*line;
	static char		buff[100 + 1];
	int				ret;

	ft_ret_val(buff, fd, &ret);
	mempush(&line, sizeof(char), 1);
	if (line == NULL)
		exit(0);
	line[0] = '\0';
	while (ret && ft_checkfd(fd, ret) == 1)
	{
		buff[ret] = '\0';
		line = ft_cattoline(buff, line);
		if (ft_isline(line) == 1 || ret < 100)
			break ;
		ret = read(fd, buff, 100);
	}
	ft_trim(buff, ret, ft_checkfd(fd, ret));
	if ((ret == 0 && line[0] == '\0') || ft_checkfd(fd, ret) == 0)
	{
		memfree(&line);
		return (NULL);
	}
	return (line);
}
