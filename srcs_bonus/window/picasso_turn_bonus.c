/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso_turn_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/21 19:48:28 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
** Functions to print sprites
*/

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
		a->sprite[c].palette =
			shadow_color(a->sprite[c].distance, a->sprite[c].palette);
		brushstroke(a->sprite[c].current_ray, a->sprite[c].point, a,
			a->sprite[c].palette);
	}
}

static void	invisible_rays(t_cub3d *a, int c)
{
	while (a->sprite[c].current_ray < 0)
	{
		a->sprite[c].xfloat += a->sprite[c].xstep;
		a->sprite[c].current_ray++;
	}
}

static void	paint(t_cub3d *a, int c)
{
	a->sprite[c].current_ray = a->sprite[c].rayinit;
	a->sprite[c].xfloat = 0;
	if (a->sprite[c].current_ray < 0)
		invisible_rays(a, c);
	while (a->sprite[c].current_ray <= a->sprite[c].rayend
		&& a->sprite[c].current_ray < a->fconf.xrendersize)
	{
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
		if ((int)a->sprite[c].xpos != (int)a->rayc.yplyr
				|| (int)a->sprite[c].ypos != (int)a->rayc.xplyr)
			if (a->sprite[c].distance > sqrt(2 * (pow(0.5, 2))))
				paint(a, c);
		if (a->sprite[c].buff)
			free(a->sprite[c].buff);
	}
}
