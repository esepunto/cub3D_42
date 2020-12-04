/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brush_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/04 14:28:29 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_cub3d *a, int x, int y, int color)
{
	char	*dst;

	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length + x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_background(t_cub3d *a)
{
	int	x;
	int	y;
	
	x = 0;
	while (x < a->fconf.xrendersize)
	{
		y = 0;
		while(y < a->fconf.yrendersize)
		{
			if (y < a->fconf.yrendersize / 2)
				my_mlx_pixel_put(a, x, y, a->fconf.ceilcolor);
			else if (y >= a->fconf.yrendersize / 2)
				my_mlx_pixel_put(a, x, y, a->fconf.floorcolor);
			y++;
		}
		x++;
	}
}

void	brush_wall(t_cub3d *a)
{
	double brush_on;
	brush_on = a->steal.initwall;
	while (brush_on < a->steal.endwall)
	{
		my_mlx_pixel_put(a, a->steal.nbr_ray, brush_on, a->steal.wallcolor);
		brush_on++;
	}
}
