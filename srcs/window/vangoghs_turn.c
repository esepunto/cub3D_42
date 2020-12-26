/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/26 05:25:01 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	brushstroke(int x, int y, t_cub3d *a, int color)
{
	char	*dst;

	if (y >= a->fconf.yrendersize || y < 0)
		return ;
	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		half_lower_wall(t_cub3d *a)
{
	int color;

	if (a->rayc.ytexturefloat < a->mlibx.xpmwall[a->rayc.wall].height
			&& a->rayc.ytexturefloat >=
			a->mlibx.xpmwall[a->rayc.wall].height / 2)
	{
		a->rayc.ytexture = (int)a->rayc.ytexturefloat;
		color = a->mlibx.xpmwall[a->rayc.wall].addr[
				a->mlibx.xpmwall[a->rayc.wall].height
				* a->rayc.ytexture + a->rayc.xtexture];
		brushstroke(a->rayc.nbr_ray, a->rayc.point + (a->fconf.yrendersize / 2),
				a, color);
		a->rayc.ytexturefloat += a->rayc.ysteptexture;
	}
	else
		return (1);
	return (0);
}

void	half_upper_wall(t_cub3d *a)
{
	int	color;

	if (a->rayc.ytexturefloat >= a->mlibx.xpmwall[a->rayc.wall].height)
		a->rayc.ytexturefloat = (a->mlibx.xpmwall[a->rayc.wall].height / 2);
	a->rayc.ytexture = (int)a->rayc.ytexturefloat;
	color = a->mlibx.xpmwall[a->rayc.wall].addr[
		a->mlibx.xpmwall[a->rayc.wall].height
		* a->rayc.ytexture + a->rayc.xtexture];
	a->rayc.point = (a->fconf.yrendersize / 2) - a->rayc.aux;
	brushstroke(a->rayc.nbr_ray, a->rayc.point, a, color);
	if (a->rayc.ytexturefloat > 0)
		a->rayc.ytexturefloat -= a->rayc.ysteptexture;
	a->rayc.aux++;
}

void	paintwalls(t_cub3d *a, int point)
{
	if (a->rayc.staturewall > a->fconf.yrendersize)
	{
		a->rayc.point = point;
		if (a->rayc.count == 0)
			a->rayc.ytexturefloat = a->mlibx.xpmwall[a->rayc.wall].height / 2;
		if (half_lower_wall(a) == 1)
			half_upper_wall(a);
		a->rayc.count++;
	}
	else
	{
		a->rayc.ytexture = (int)a->rayc.ytexturefloat;
		a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
			a->mlibx.xpmwall[a->rayc.wall].height
			* a->rayc.ytexture + a->rayc.xtexture];
		a->rayc.ytexturefloat += a->rayc.ysteptexture;
		brushstroke(a->rayc.nbr_ray, point, a, a->rayc.palette);
	}
}

void	pointillism(t_cub3d *a)
{
	int	point;

	a->rayc.count = 0;
	point = 0;
	while (point < a->fconf.yrendersize || point < a->rayc.staturewall)
	{
		if (point < a->rayc.initwall)
			brushstroke(a->rayc.nbr_ray, point, a, a->fconf.ceilcolor);
		else if (point >= a->rayc.endwall)
			brushstroke(a->rayc.nbr_ray, point, a, a->fconf.floorcolor);
		else
			paintwalls(a, point);
		point++;
	}
}
