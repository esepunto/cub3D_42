/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso_turn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 23:46:58 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
** Functions to print sprites
*/

int			dark_color_sprite(t_cub3d *a, int nb_spr, int color)
{
	double	dark;
	int		c[3];
	int		dc[3];
	int		rtn;

	dark = 2.5 / a->sprite[nb_spr].distance;
	c[0] = (color >> 16) & 255;
	c[1] = (color >> 8) & 255;
	c[2] = color & 255;
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

static void	spr_calc_palette(t_cub3d *a, int c, int kill)
{
	a->sprite[c].ysprite = (int)a->sprite[c].yfloat
		& (a->mlibx.object[kill].height - 1);
	a->sprite[c].xsprite = (int)a->sprite[c].xfloat
		& (a->mlibx.object[kill].width - 1);
	a->sprite[c].palette = a->mlibx.object[kill].addr[
		a->mlibx.object[kill].height
		* a->sprite[c].ysprite
		+ a->sprite[c].xsprite];
	if ((a->sprite[c].palette & 0x00FFFFFF) != 0)
	{
		a->sprite[c].palette = dark_color_sprite(a, c, a->sprite[c].palette);
		brushstroke(a->sprite[c].current_ray, a->sprite[c].point, a,
			a->sprite[c].palette);
	}
}

static void	paint_spr(t_cub3d *a, int c)
{
	a->sprite[c].current_ray = a->sprite[c].rayinit;
	a->sprite[c].xfloat = 0;
	while (a->sprite[c].current_ray <= a->sprite[c].rayend
		&& a->sprite[c].current_ray < a->fconf.xrendersize)
	{
		while (a->sprite[c].current_ray < 0)
		{
			a->sprite[c].xfloat += a->sprite[c].xstep;
			a->sprite[c].current_ray++;
		}
		if (a->sprite[c].buff[a->sprite[c].current_ray].ray == true)
		{
			a->sprite[c].yfloat = 0;
			a->sprite[c].point = a->sprite[c].init;
			while (a->sprite[c].point <= a->sprite[c].end)
			{
				spr_calc_palette(a, c, a->sprite[c].killer);
				a->sprite[c].yfloat += a->sprite[c].ystep;
				a->sprite[c].point++;
			}
		}
		a->sprite[c].xfloat += a->sprite[c].xstep;
		a->sprite[c].current_ray++;
	}
}

static void	sort_sprites(t_cub3d *a)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < a->fconf.map.nbr_sprite)
	{
		j = i + 1;
		while (j < a->fconf.map.nbr_sprite)
		{
			if (a->sprite[j].distance < a->sprite[i].distance)
			{
				temp = a->sprite[j];
				a->sprite[j] = a->sprite[i];
				a->sprite[i] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
** For visual reasons, only prints those sprites
** whose are at least at distance of the radius of the
** circle circunscribed to every ceil.
** Calc with Pythagoras:
** radius (minimum distance to print) = sqtr( 2 * ( (square ceil / 2) ^ 2) )
*/

void		paintsprites(t_cub3d *a)
{
	int	c;

	sort_sprites(a);
	c = a->fconf.map.num_sprites;
	while (--c >= 0)
	{
		while (a->sprite[c].view == false)
			c--;
		calc_init_ray(a, c);
		paint_spr(a, c);
		if (a->sprite[c].buff)
			free(a->sprite[c].buff);
	}
}
