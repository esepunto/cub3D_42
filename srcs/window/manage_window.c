/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:23:45 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/24 13:23:45 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		closed(t_cub3d *a)
{
	mlx_destroy_window(a->mlibx.mlx, a->mlibx.win);
	system("leaks cub3D");
	exit(0);
}

/*
**  To close windows when type ESCC with mlx_key_hook
*/

int		caress_key(int keycode, t_cub3d *a)
{
	if (keycode == KEY_ESC)
		closed(a);
	return (0);
}

/*
**  To close windows when type ESCC with mlx_hook
*/

int 	key_press(int keycode, t_cub3d *a)
{
	if (keycode == KEY_ESC)
		closed(a);
	return (0);
}

void	init_window(t_cub3d *a)
{
	a->mlibx.mlx = mlx_init();
	a->mlibx.img = mlx_new_image(a->mlibx.mlx,
			a->fconf.xrendersize, a->fconf.yrendersize);
	a->mlibx.win = mlx_new_window(a->mlibx.mlx,
			a->fconf.xrendersize, a->fconf.yrendersize, "cub3D");
	mlx_key_hook(a->mlibx.win, caress_key, a);//This ft or mlx_hook to close windows when type ESC
	mlx_hook(a->mlibx.win, 17, 1L << 17, closed, a);
	mlx_hook(a->mlibx.win, 2, 1L << 17, key_press, a);
	mlx_loop(a->mlibx.mlx);
}
