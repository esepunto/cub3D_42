/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangogh_turn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 19:15:04 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
** Functions to print walls
*/

static int		dark_color_wall(t_cub3d *a)
{
	double	dark;
	int		c[3];
	int		dc[3];
	int		rtn;

	dark = (2.5 / a->rayc.distance);
	c[0] = (a->rayc.palette >> 16) & 255;
	c[1] = (a->rayc.palette >> 8) & 255;
	c[2] = a->rayc.palette & 255;
	dc[0] = (int)(c[0] * dark);
	dc[1] = (int)(c[1] * dark);
	dc[2] = (int)(c[2] * dark);
	if (dc[0] > c[0])
		dc[0] = c[0];
	if (dc[1] > c[1])
		dc[1] = c[1];
	if (dc[2] > c[2])
		dc[2] = c[2];
	rtn = (dc[0] * 256 * 256) + (dc[1] * 256) + dc[2];
	return (rtn);
}

void		brushstroke(int x, int y, t_cub3d *a, int color)
{
	char	*dst;

	if (y >= a->fconf.yrendersize || y < 0)
		return ;
	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	calc_palette(t_cub3d *a)
{
	a->rayc.ytexture = (int)a->rayc.ytexturefloat
		& (a->mlibx.xpmwall[a->rayc.wall].height - 1);
	a->rayc.palette = a->mlibx.xpmwall[a->rayc.wall].addr[
		a->mlibx.xpmwall[a->rayc.wall].height
		* a->rayc.ytexture + a->rayc.xtexture];
	
	if ((a->rayc.palette & 0x00FFFFFF) != 0)
	{
		a->rayc.palette = dark_color_wall(a);
		brushstroke(a->rayc.nbr_ray, a->rayc.point, a, a->rayc.palette);
	}
}

/*
** To paint wall when player is close to the wall and
** its ocuppes all the screen, first paints lower half of
** the wall and then paints upper half.
** To paint both halves, starts from just half of the screen
** and paints throw the extreme.
*/

static void	close2wall(t_cub3d *a)
{
	if (a->rayc.ytexturefloat < a->mlibx.xpmwall[a->rayc.wall].height
			&& a->rayc.ytexturefloat >=
			a->mlibx.xpmwall[a->rayc.wall].height / 2.0)
	{
		a->rayc.point += (a->fconf.yrendersize / 2);
		if (a->rayc.point <= a->fconf.yrendersize)
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
		if (a->rayc.point >= 0)
			calc_palette(a);
		a->rayc.ytexturefloat -= a->rayc.ysteptexture;
		a->rayc.aux++;
	}
}

static void	paintwalls(t_cub3d *a, int point)
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

void		pointillism(t_cub3d *a)
{
	int	point;

	calc_texturing(a);
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
