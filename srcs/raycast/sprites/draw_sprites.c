/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/31 18:09:17 by ssacrist         ###   ########.fr       */
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
		& (a->mlibx.sprite[c].height - 1);
	a->rayc.palette = a->fconf.ceilcolor;
/*	a->rayc.palette = a->mlibx.sprite[c].addr[
		a->mlibx.sprite[c].height
		* a->mlibx.sprite[c].y + a->mlibx.sprite[c].x];
*/	spr_brushstroke(a->rayc.nbr_ray, a->rayc.point, a, a->rayc.palette);
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

void	spr_paintwalls(t_cub3d *a, int point, int c)
{
	a->mlibx.sprite[c].point = point;
	if (a->mlibx.sprite[c].stature > a->fconf.yrendersize)
	{
		if (a->mlibx.sprite[c].count == 0)
			a->mlibx.sprite[c].yfloat = a->mlibx.sprite[c].height / 2.0;
		spr_close2wall(a, c);
		a->mlibx.sprite[c].count++;
	}
	else
	{
		spr_calc_palette(a, c);
		a->mlibx.sprite[c].yfloat += a->mlibx.sprite[c].yfloat;
	}
}

/*
**  stature_sprite = (xrendersize / dist_muro) * dist_sprite
*/

void	calc_stature_sprite(t_cub3d *a, int point)
{
	int	c;

//	point = 0;//quitar
	c = 0;
	while (c < a->fconf.map.num_sprites)
	{
		a->mlibx.sprite[c].stature =
			(a->rayc.staturewall / a->mlibx.sprite[c].dist_sprite)
			* a->rayc.distance;
		a->mlibx.sprite[c].xaux = tan(a->mlibx.sprite[c].angle)
				* a->mlibx.sprite[c].dist_sprite;
		a->mlibx.sprite[c].x = a->fconf.xrendersize / 2 + a->mlibx.sprite[c].xaux
				- a->mlibx.sprite[c].width / 2;
		a->mlibx.sprite[c].aux = 0;
		a->mlibx.sprite[c].ystep = 1.0 * a->mlibx.sprite[c].height
			/ a->mlibx.sprite[c].stature;
//		Revisar esta función
//		a->>mlibx.sprite[c].yfloat = a->>mlibx.sprite[c].ystep *
//			(a->rayc.initwall + a->rayc.staturewall / 2
//			- a->fconf.yrendersize / 2);
		spr_paintwalls(a, point, c);
		c++;
	}
}

void	paintsprites(t_cub3d *a, int point)
{
	sort_sprites(a);
	calc_stature_sprite(a, point);
}
