/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:40:28 by ntan              #+#    #+#             */
/*   Updated: 2022/05/31 14:34:53 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

void	ending_3(t_prog *cub3d)
{
	if (cub3d->select1.image)
		mlx_destroy_image(cub3d->mlx, cub3d->select1.image);
	if (cub3d->select2.image)
		mlx_destroy_image(cub3d->mlx, cub3d->select2.image);
	if (cub3d->punch1.image)
		mlx_destroy_image(cub3d->mlx, cub3d->punch1.image);
	if (cub3d->punch2.image)
		mlx_destroy_image(cub3d->mlx, cub3d->punch2.image);
	if (cub3d->punch3.image)
		mlx_destroy_image(cub3d->mlx, cub3d->punch3.image);
	if (cub3d->gun1.image)
		mlx_destroy_image(cub3d->mlx, cub3d->gun1.image);
	if (cub3d->gun2.image)
		mlx_destroy_image(cub3d->mlx, cub3d->gun2.image);
	if (cub3d->gun3.image)
		mlx_destroy_image(cub3d->mlx, cub3d->gun3.image);
	if (cub3d->gun4.image)
		mlx_destroy_image(cub3d->mlx, cub3d->gun4.image);
	if (cub3d->gun5.image)
		mlx_destroy_image(cub3d->mlx, cub3d->gun5.image);
}

void	ending_2(t_prog *cub3d)
{
	if (cub3d->minimap_ext.image)
		mlx_destroy_image(cub3d->mlx, cub3d->minimap_ext.image);
	if (cub3d->minimap_int.image)
		mlx_destroy_image(cub3d->mlx, cub3d->minimap_int.image);
	if (cub3d->tmp_img.image)
		mlx_destroy_image(cub3d->mlx, cub3d->tmp_img.image);
	if (cub3d->ea_text_img.image)
		mlx_destroy_image(cub3d->mlx, cub3d->ea_text_img.image);
	if (cub3d->we_text_img.image)
		mlx_destroy_image(cub3d->mlx, cub3d->we_text_img.image);
	if (cub3d->so_text_img.image)
		mlx_destroy_image(cub3d->mlx, cub3d->so_text_img.image);
	if (cub3d->no_text_img.image)
		mlx_destroy_image(cub3d->mlx, cub3d->no_text_img.image);
	ending_3(cub3d);
}

int	ending(t_prog *cub3d)
{
	ending_2(cub3d);
	if (cub3d->door1.image)
		mlx_destroy_image(cub3d->mlx, cub3d->door1.image);
	if (cub3d->door2.image)
		mlx_destroy_image(cub3d->mlx, cub3d->door2.image);
	if (cub3d->door3.image)
		mlx_destroy_image(cub3d->mlx, cub3d->door3.image);
	if (cub3d->door4.image)
		mlx_destroy_image(cub3d->mlx, cub3d->door4.image);
	if (cub3d->door5.image)
		mlx_destroy_image(cub3d->mlx, cub3d->door5.image);
	if (cub3d->door6.image)
		mlx_destroy_image(cub3d->mlx, cub3d->door6.image);
	if (cub3d->minimap_door.image)
		mlx_destroy_image(cub3d->mlx, cub3d->minimap_door.image);
	if (cub3d->win)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	memrelease();
	exit(0);
}

t_image	create_sprite(t_prog *cub3d, void *mlx, char *path)
{
	t_image	sprite;

	sprite.image = mlx_xpm_file_to_image(mlx, path, &sprite.size_x,
			&sprite.size_y);
	if (!sprite.image)
	{
		printf("Error\nAn image is missing\n");
		ending(cub3d);
	}
	sprite.addr = mlx_get_data_addr(sprite.image, &sprite.bits_per_pixel,
			&sprite.line_length, &sprite.endian);
	return (sprite);
}

void	init_window(t_prog *cub3d, int widht, int height, char *name)
{
	cub3d->win = mlx_new_window(cub3d->mlx, widht, height, name);
	cub3d->win_x = widht;
	cub3d->win_y = height;
}
