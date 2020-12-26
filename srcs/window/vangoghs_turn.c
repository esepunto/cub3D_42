/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/26 11:58:13 by ssacrist         ###   ########.fr       */
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

void	calc_palette(t_cub3d *a)
{
	a->rayc.ytexture = (int)a->rayc.ytexturefloat
		& (a->mlibx.xpmwall[a->rayc.wall].height - 1);
	a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
		a->mlibx.xpmwall[a->rayc.wall].height
		* a->rayc.ytexture + a->rayc.xtexture];
	brushstroke(a->rayc.nbr_ray, a->rayc.point, a, a->rayc.palette);
}

/*
** To paint wall when player is close to the wall and
** its ocuppes all the screen, first paints lower half of
** the wall and then paints upper half.
** To paint both halves, starts from just half of the screen
** and paints throw the extreme.
*/

void	close2wall(t_cub3d *a)
{
	if (a->rayc.ytexturefloat < a->mlibx.xpmwall[a->rayc.wall].height
			&& a->rayc.ytexturefloat >=
			a->mlibx.xpmwall[a->rayc.wall].height / 2.0)
	{
		a->rayc.point += (a->fconf.yrendersize / 2);
		calc_palette(a);
		a->rayc.ytexturefloat += a->rayc.ysteptexture;
	}
	else
	{
		if (a->rayc.ytexturefloat >= a->mlibx.xpmwall[a->rayc.wall].height)
		{
			a->rayc.ytexturefloat =
				(a->mlibx.xpmwall[a->rayc.wall].height / 2.0);
		}
		a->rayc.point = (int)((a->fconf.yrendersize / 2) - 1 - a->rayc.aux);
		calc_palette(a);
		a->rayc.ytexturefloat -= a->rayc.ysteptexture;
		a->rayc.aux++;
	}
}

void	paintwalls(t_cub3d *a, int point)
{
	a->rayc.point = point;
	if (a->rayc.staturewall > a->fconf.yrendersize)
	{
		if (a->rayc.count == 0)
			a->rayc.ytexturefloat = a->mlibx.xpmwall[a->rayc.wall].height / 2.0;
		close2wall(a);
		a->rayc.count++;
	}
	else
	{
		calc_palette(a);
		a->rayc.ytexturefloat += a->rayc.ysteptexture;
	}
}

void	pointillism(t_cub3d *a)
{
	int	point;

	a->rayc.count = 0;
	point = 0;
	while (point <= a->fconf.yrendersize || point <= a->rayc.staturewall)
	{
		if (point <= a->rayc.initwall)
			brushstroke(a->rayc.nbr_ray, point, a, a->fconf.ceilcolor);
		else if (point < a->rayc.endwall)
			paintwalls(a, point);
		else
			brushstroke(a->rayc.nbr_ray, point, a, a->fconf.floorcolor);
		point++;
	}
}
