/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/24 02:49:47 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	brushstroke(int x, int y, t_cub3d *a)
{
	char	*dst;

	if (y > a->fconf.yrendersize)
		return;
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


void	wall_so_close(t_cub3d *a, int point)
{
	if (a->rayc.count == 0)
		a->rayc.ytexturefloat = a->mlibx.xpmwall[a->rayc.wall].img_height / 2;
	if (a->rayc.ytexturefloat < a->mlibx.xpmwall[a->rayc.wall].img_height
				&& a->rayc.ytexturefloat >= a->mlibx.xpmwall[a->rayc.wall].img_height / 2)
		{
			a->rayc.ytexture = (int)a->rayc.ytexturefloat;
			a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
					a->mlibx.xpmwall[a->rayc.wall].img_height
					* a->rayc.ytexture + a->rayc.xtexture];
			brushstroke(a->rayc.nbr_ray, point + (a->fconf.yrendersize / 2), a);
			a->rayc.ytexturefloat += a->rayc.ysteptexture;
		}
	else
	{
		printf("test");
		if (a->rayc.ytexturefloat >= a->mlibx.xpmwall[a->rayc.wall].img_height)
		{
			a->rayc.ytexturefloat = (a->mlibx.xpmwall[a->rayc.wall].img_height / 2) - 1;
		}
		a->rayc.ytexture = (int)a->rayc.ytexturefloat;
		a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
				a->mlibx.xpmwall[a->rayc.wall].img_height
				* a->rayc.ytexture + a->rayc.xtexture];
		if (a->rayc.ytexturefloat > 0)
			a->rayc.ytexturefloat -= a->rayc.ysteptexture;
	}
//	print_wall(a);
	printf("addr: %d\n", a->mlibx.xpmwall[a->rayc.wall].img_height * a->rayc.ytexture + a->rayc.xtexture);
	print_direction(a);
//	printf("stature: %f\n", a->rayc.staturewall);
	a->rayc.count++;
}



void	pointillism(t_cub3d *a)
{
	int	point;

	a->rayc.count = 0;
	point = 0;
	while (point < a->fconf.yrendersize)
	{
		if (point < a->rayc.initwall)
		{
			a->rayc.palette = a->fconf.ceilcolor;
			brushstroke(a->rayc.nbr_ray, point, a);
		}
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
			if (a->rayc.staturewall > a->fconf.yrendersize)
				wall_so_close(a, point);
			else
			{
				a->rayc.ytexture = (int)a->rayc.ytexturefloat;
				a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
					a->mlibx.xpmwall[a->rayc.wall].img_height
					* a->rayc.ytexture + a->rayc.xtexture];
				a->rayc.ytexturefloat += a->rayc.ysteptexture;
				brushstroke(a->rayc.nbr_ray, point, a);
			}
		}
		else if (point >= a->rayc.endwall)
		{
			a->rayc.palette = a->fconf.floorcolor;
			brushstroke(a->rayc.nbr_ray, point, a);
		}
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
