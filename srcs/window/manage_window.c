/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:23:45 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/04 13:06:40 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		raycast(t_cub3d *a)
{
	mlx_hook(a->mlibx.win, 2, 1L << 17, caress_key, a);
	return (0);
}

void	init_window(t_cub3d *a)
{
	a->mlibx.mlx = mlx_init();
	a->mlibx.img.img = mlx_new_image(a->mlibx.mlx, a->fconf.xrendersize,
			a->fconf.yrendersize);
	a->mlibx.img.addr = mlx_get_data_addr(a->mlibx.img.img,
			&a->mlibx.img.bits_per_pixel, &a->mlibx.img.line_length,
			&a->mlibx.img.endian);
	a->mlibx.win = mlx_new_window(a->mlibx.mlx, a->fconf.xrendersize,
			a->fconf.yrendersize, "cub3D");
	draw(a);
	mlx_hook(a->mlibx.win, 17, 1L << 17, closed, a);
	mlx_loop_hook(a->mlibx.mlx, &raycast, a);
	mlx_loop(a->mlibx.mlx);
}
