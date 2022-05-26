/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:26:39 by ntan              #+#    #+#             */
/*   Updated: 2022/05/26 14:51:02 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	update(t_prog *cub3d)
{
	void	*tmp;

	tmp = cub3d->tmp_img.image;
	newimage(cub3d);
	raycasting(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->tmp_img.image, 0, 0);
	draw_map(cub3d);
	draw_player(cub3d);
	if (tmp)
		mlx_destroy_image(cub3d->mlx, tmp);
	return (0);
}

void	check_exit(t_prog *cub3d)
{
	static int	i = 0;

	if (cub3d->map[(int) cub3d->py / PXLS][(int) cub3d->px / PXLS] == 'D'
		|| i > 0)
	{
		i++;
		printf("CONGRATULATIONS YOU WON !\n");
		if (i == 10)
			ending(cub3d);
	}
}

void	weapons_select(t_prog *cub3d)
{
	if (cub3d->weapons == 0)
		punch(cub3d);
	else if (cub3d->weapons == 1)
		gun(cub3d);
}

int	mouse_hook(t_prog *cub3d)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(cub3d->mlx, cub3d->win, &x, &y);
	if (x >= 0 && x <= SCREEN_W / 14)
		left_arrow(cub3d, 0.1);
	else if (x > SCREEN_W / 14 && x <= SCREEN_W / 7)
		left_arrow(cub3d, 0.03);
	else if (x > SCREEN_W / 7 && x <= SCREEN_W / 7 * 2)
		left_arrow(cub3d, 0.03);
	else if (x > SCREEN_W / 7 * 2 && x <= SCREEN_W / 7 * 3)
		left_arrow(cub3d, 0.015);
	else if (x >= SCREEN_W / 7 * 4 && x <= SCREEN_W / 7 * 5)
		right_arrow(cub3d, 0.015);
	else if (x > SCREEN_W / 7 * 5 && x <= SCREEN_W / 7 * 6)
		right_arrow(cub3d, 0.03);
	else if (x > SCREEN_W / 7 * 6 && x <= SCREEN_W / 14 * 13)
		right_arrow(cub3d, 0.05);
	else if (x > SCREEN_W / 14 * 13 && x <= SCREEN_W)
		right_arrow(cub3d, 0.1);
	door_animation(cub3d);
	check_exit(cub3d);
	update(cub3d);
	weapons_select(cub3d);
	return (0);
}

void	import_sprites(t_prog *cub3d)
{
	cub3d->minimap_ext = create_sprite(cub3d, cub3d->mlx, "bonus/img/11.xpm");
	cub3d->minimap_int = create_sprite(cub3d, cub3d->mlx, "bonus/img/12.xpm");
	cub3d->minimap_door = create_sprite
		(cub3d, cub3d->mlx, "bonus/img/minimap_door.xpm");
	cub3d->no_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->no_text);
	cub3d->so_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->so_text);
	cub3d->we_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->we_text);
	cub3d->ea_text_img = create_sprite(cub3d, cub3d->mlx, cub3d->ea_text);
	cub3d->door1 = create_sprite(cub3d, cub3d->mlx, "bonus/img/1.xpm");
	cub3d->door2 = create_sprite(cub3d, cub3d->mlx, "bonus/img/2.xpm");
	cub3d->door3 = create_sprite(cub3d, cub3d->mlx, "bonus/img/3.xpm");
	cub3d->door4 = create_sprite(cub3d, cub3d->mlx, "bonus/img/4.xpm");
	cub3d->door5 = create_sprite(cub3d, cub3d->mlx, "bonus/img/5.xpm");
	cub3d->door6 = create_sprite(cub3d, cub3d->mlx, "bonus/img/6.xpm");
	cub3d->punch1 = create_sprite(cub3d, cub3d->mlx, "bonus/img/punch1.xpm");
	cub3d->punch2 = create_sprite(cub3d, cub3d->mlx, "bonus/img/punch2.xpm");
	cub3d->punch3 = create_sprite(cub3d, cub3d->mlx, "bonus/img/punch3.xpm");
	cub3d->gun1 = create_sprite(cub3d, cub3d->mlx, "bonus/img/gun1.xpm");
	cub3d->gun2 = create_sprite(cub3d, cub3d->mlx, "bonus/img/gun2.xpm");
	cub3d->gun3 = create_sprite(cub3d, cub3d->mlx, "bonus/img/gun3.xpm");
	cub3d->gun4 = create_sprite(cub3d, cub3d->mlx, "bonus/img/gun4.xpm");
	cub3d->gun5 = create_sprite(cub3d, cub3d->mlx, "bonus/img/gun5.xpm");
}

int	game_loop(t_prog *cub3d)
{
	cub3d->pdx = cos(cub3d->pa) * 5;
	cub3d->pdy = sin(cub3d->pa) * 5;
	cub3d->plane_x = cos(cub3d->pa + PI / 2) * 5;
	cub3d->plane_y = sin(cub3d->pa + PI / 2) * 5;
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (1);
	import_sprites(cub3d);
	init_window(cub3d, 1280, 720, "cub3d");
	mlx_do_key_autorepeaton(cub3d->mlx);
	mlx_hook(cub3d->win, 17, 0, ending, cub3d);
	mlx_hook(cub3d->win, 2, (1L << 0), input, cub3d);
	mlx_loop_hook(cub3d->mlx, mouse_hook, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}
