/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/22 16:15:34 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	brushstroke(int x, int y, t_cub3d *a)
{
	char	*dst;

	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = a->rayc.palette;
}

void	my_mlx_pixel_put(t_cub3d *a, int x, int y, int color)
{
	char	*dst;

	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void	wall_so_close(t_cub3d *a)
{
	static int c = 0;
	
	if (c == 0)
		a->rayc.ytexturefloat = a->mlibx.xpmwall[a->rayc.wall].img_height / 2;
	if (a->rayc.ytexturefloat < a->mlibx.xpmwall[a->rayc.wall].img_height)
		a->rayc.ytexturefloat += a->rayc.ysteptexture;
	else 
	{
		if (a->rayc.ytexturefloat >= a->mlibx.xpmwall[a->rayc.wall].img_height)
			a->rayc.ytexturefloat = (a->mlibx.xpmwall[a->rayc.wall].img_height / 2) - 1;
		if (a->rayc.ytexturefloat > 0)
			a->rayc.ytexturefloat -= a->rayc.ysteptexture;
	}
//	print_direction(a);
//	printf("%d: wall so close\n", c);
//	printf("stature: %f\n", a->rayc.staturewall);
	c++;
}



void	pointillism(t_cub3d *a)
{
	int	point;

	point = 0;
	while (point < a->fconf.yrendersize)
	{
		if (point < a->rayc.initwall)
			a->rayc.palette = a->fconf.ceilcolor;
		else if (point < a->rayc.endwall)
		{
/*			if (a->rayc.ytexturefloat < 0)
				a->rayc.ytexturefloat = 0;
			if (a->rayc.ytexturefloat >
						a->mlibx.xpmwall[a->rayc.wall].img_height - 1)
			{
				a->rayc.ytexturefloat =
						a->mlibx.xpmwall[a->rayc.wall].img_height - 1;
			}
*/			
			a->rayc.ytexture = (int)a->rayc.ytexturefloat;
			
			a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
					a->mlibx.xpmwall[a->rayc.wall].img_height
					* a->rayc.ytexture + a->rayc.xtexture];

			if (a->rayc.staturewall > a->fconf.yrendersize)
				wall_so_close(a);
			else
				a->rayc.ytexturefloat += a->rayc.ysteptexture;
		}
		else if (point >= a->rayc.endwall)
			a->rayc.palette = a->fconf.floorcolor;
		brushstroke(a->rayc.nbr_ray, point, a);
		point++;
	}
}

/* 			if (a->rayc.ytexturefloat < 0)
				a->rayc.ytexturefloat = 0;
			if (a->rayc.ytexturefloat >
						a->mlibx.xpmwall[a->rayc.wall].img_height - 1)
			{
				a->rayc.ytexturefloat =
						a->mlibx.xpmwall[a->rayc.wall].img_height - 1;
			} */
