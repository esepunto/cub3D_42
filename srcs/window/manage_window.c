/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:23:45 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/26 20:22:30 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
**  To close windows when type ESCC with mlx_key_hook
*/

int		caress_key(int keycode, t_cub3d *a)
{
//	printf("Hola\n");
	a->rayc.keycode = keycode;
	if (keycode == KEY_ESC)
		closed(a);
	if (keycode == KEY_MOVE_FRONT)
		go_front(a);
	if (keycode == KEY_MOVE_BACK)
		go_back(a);
	if (keycode == KEY_MOVE_RIGHT)
		go_right(a);
	if (keycode == KEY_MOVE_LEFT)
		go_left(a);
	if (keycode == KEY_LOOK_RIGHT)
		rotate_right(a);
	if (keycode == KEY_LOOK_LEFT)
		rotate_left(a);
//	print_struct(a);
	keycode = 42;
	init_raycast(a);
	return (0);
}

/*
**  To close windows when type ESCC with mlx_hook
*/
/*
int 	key_press(int keycode, t_cub3d *a)
{
	init_raycast(a);
	if (keycode == KEY_ESC)
		closed(a);
	if (keycode == KEY_MOVE_FRONT)
		go_front(a);
	if (keycode == KEY_MOVE_BACK)
		go_back(a);
	if (keycode == KEY_MOVE_RIGHT)
		go_right(a);
	if (keycode == KEY_MOVE_LEFT)
		go_left(a);
	if (keycode == KEY_LOOK_RIGHT)
		rotate_right(a);
	if (keycode == KEY_LOOK_LEFT)
		rotate_left(a);
	init_raycast(a);
	printf("xpos: %f - ", a->rayc.xpos);
	printf("ypos: %f\n", a->rayc.ypos);
	printf("xdir: %f - ", a->rayc.xdir);
	printf("ydir: %f\n", a->rayc.ydir);
	printf("xcamera: %f - ", a->rayc.xcamera);
	printf("ycamera: %f\n", a->rayc.ycamera);
	printf("xmap: %d - ", a->rayc.xmap);
	printf("ymap: %d\n", a->rayc.ymap);
	printf("key: %d\n\n", keycode);
	return (0);
}
*/

int		prueba(t_cub3d *a)
{
	mlx_hook(a->mlibx.win, 2, 1L << 17, caress_key, a);
//	init_raycast(a);
	return (0);
}

void	init_window(t_cub3d *a)
{
	a->mlibx.mlx = mlx_init();
	a->mlibx.img = mlx_new_image(a->mlibx.mlx,
			a->fconf.xrendersize, a->fconf.yrendersize);
	a->mlibx.win = mlx_new_window(a->mlibx.mlx,
			a->fconf.xrendersize, a->fconf.yrendersize, "cub3D");
//	mlx_key_hook(a->mlibx.win, caress_key, a);//This ft or mlx_hook to close windows when type ESC
	init_raycast(a);
	mlx_hook(a->mlibx.win, 17, 1L << 17, closed, a);
//	mlx_hook(a->mlibx.win, 2, 1L << 17, caress_key, a);
//	mlx_loop_hook(a->mlibx.mlx, &init_raycast, a);
//	mlx_loop_hook(a->mlibx.mlx, &caress_key, a);
	mlx_loop_hook(a->mlibx.mlx, &prueba, a);
	mlx_loop(a->mlibx.mlx);
}
