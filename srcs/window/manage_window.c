/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:23:45 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 14:26:17 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_window(t_cub3d *a)
{
	a->mlibx.mlx = mlx_init();
	a->mlibx.win = mlx_new_window(a->mlibx.mlx,
			a->fconf.xrendersize, a->fconf.yrendersize, "cub3D");
	mlx_loop(a->mlibx.mlx);
}
