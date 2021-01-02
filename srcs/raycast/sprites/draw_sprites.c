/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/02 13:40:14 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	spr_brushstroke(int x, int y, t_cub3d *a, int color)
{
	char	*dst;

	if (y >= a->fconf.yrendersize || y < 0)
		return ;
	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	spr_calc_palette(t_cub3d *a, int c)
{
	a->mlibx.sprite[c].y = (int)a->mlibx.sprite[c].yfloat
		& (a->mlibx.xpmwall[4].height - 1);
//	a->mlibx.sprite[c].palette = a->fconf.ceilcolor;
	a->mlibx.sprite[c].palette = a->mlibx.xpmwall[4].addr[
		a->mlibx.xpmwall[4].height
		* a->mlibx.sprite[c].y + a->mlibx.sprite[c].x];
	spr_brushstroke(a->rayc.nbr_ray, a->mlibx.sprite[c].point, a, a->mlibx.sprite[c].palette);
}

/*
** To paint wall when player is close to the sprite and
** its ocuppes all the screen, first paints lower half of
** the sprite and then paints upper half.
** To paint both halves, starts from just half of the screen
** and paints throw the extreme.
*/

void	spr_close2wall(t_cub3d *a, int c)
{
	if (a->mlibx.sprite[c].yfloat < a->mlibx.sprite[c].height
			&& a->mlibx.sprite[c].yfloat >=
			a->mlibx.sprite[c].height / 2.0)
	{
		a->mlibx.sprite[c].point += (a->fconf.yrendersize / 2);
		if (a->mlibx.sprite[c].point <= a->fconf.yrendersize)
			spr_calc_palette(a, c);
		a->mlibx.sprite[c].yfloat += a->mlibx.sprite[c].yfloat;
	}
	else
	{
		if (a->mlibx.sprite[c].yfloat >= a->mlibx.sprite[c].height)
		{
			a->mlibx.sprite[c].yfloat =
				(a->mlibx.sprite[c].height / 2.0);
		}
		a->mlibx.sprite[c].point = (int)((a->fconf.yrendersize / 2) - 1 - a->mlibx.sprite[c].aux);
		if (a->mlibx.sprite[c].point >= 0)
			spr_calc_palette(a, c);
		a->mlibx.sprite[c].yfloat -= a->mlibx.sprite[c].yfloat;
		a->mlibx.sprite[c].aux++;
	}
}

void	paint_spr(t_cub3d *a, int point, int c)
{
	if (point < a->mlibx.sprite[c].init || point > a->mlibx.sprite[c].end)
		return ;
	a->mlibx.sprite[c].point = point;
/*	if (a->mlibx.sprite[c].stature > a->fconf.yrendersize)
	{
		if (a->mlibx.sprite[c].count == 0)
			a->mlibx.sprite[c].yfloat = a->mlibx.sprite[c].height / 2.0;
		spr_close2wall(a, c);
		a->mlibx.sprite[c].count++;
	}
	else
	{*/
//	a->mlibx.sprite[c].point = point;
	spr_calc_palette(a, c);
	a->mlibx.sprite[c].yfloat += a->mlibx.sprite[c].ystep;
//	}
}

void	paintsprites(t_cub3d *a, int point)
{
	int	c;
	
	sort_sprites(a);
	c = -1;
	while (++c < a->fconf.map.num_sprites)
		paint_spr(a, point, c);
}
