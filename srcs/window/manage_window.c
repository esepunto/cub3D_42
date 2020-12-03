/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:23:45 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/03 11:37:45 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
**  To close windows when type ESCC with mlx_key_hook
*/

int		caress_key(int keycode, t_cub3d *a)
{

	a->rayc.keycode = keycode;
	if (keycode == KEY_ESC)
		closed(a);
	else if (keycode == KEY_MOVE_FRONT)
		go_front(a);
	else if (keycode == KEY_MOVE_BACK)
		go_back(a);
	else if (keycode == KEY_MOVE_RIGHT)
		go_right(a);
	else if (keycode == KEY_MOVE_LEFT)
		go_left(a);
	else if (keycode == KEY_LOOK_RIGHT)
		rotate_right(a);
	else if (keycode == KEY_LOOK_LEFT)
		rotate_left(a);
	draw_minimap(a);
	init_raycast(a);
	return (0);
}

int		prueba(t_cub3d *a)
{
//	mlx_hook(a->mlibx.win, 2, 1L << 17, caress_key, a);
	mlx_hook(a->mlibx.win, 2, 1L << 17, teclado, a);
	return (0);
}

void	init_window(t_cub3d *a)
{
	a->mlibx.mlx = mlx_init();
	a->mlibx.img.img = mlx_new_image(a->mlibx.mlx, a->fconf.xrendersize, a->fconf.yrendersize);
	a->mlibx.win = mlx_new_window(a->mlibx.mlx, a->fconf.xrendersize, a->fconf.yrendersize, "cub3D");
//	draw_minimap(a);
	a->mlibx.img.addr = mlx_get_data_addr(a->mlibx.img.img, &a->mlibx.img.bits_per_pixel, &a->mlibx.img.line_length, &a->mlibx.img.endian);
	draw(a);
	//a->mlibx.img.addr = mlx_get_data_addr(a->mlibx.img.img, &a->mlibx.img.bits_per_pixel, &a->mlibx.img.line_length, &a->mlibx.img.endian);
//	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
	mlx_hook(a->mlibx.win, 17, 1L << 17, closed, a);
	mlx_loop_hook(a->mlibx.mlx, &prueba, a);
	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
//	mlx_destroy_image(a->mlibx.mlx, a->mlibx.img.img);
	mlx_loop(a->mlibx.mlx);
}
