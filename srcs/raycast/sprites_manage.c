/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/17 21:37:53 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		allocate_sprite(t_cub3d *a)
{
	if (!(a->sprite[a->fconf.map.nbr_sprite].buff =
			calloc(sizeof(a->sprite[a->fconf.map.nbr_sprite].buff),
			a->fconf.xrendersize * sizeof(t_buffer))))
		msg_err("No memory for buffer!");
}

static t_sprite	calc_distance_nd_stature(t_cub3d *a, t_sprite sprite)
{
	sprite.distance = hypot(
				((int)a->rayc.xray + 0.5) - a->rayc.xplyr,
				((int)a->rayc.yray + 0.5) - a->rayc.yplyr)
				* cos(a->rayc.anglray - a->rayc.dirplyr);
	sprite.stature = a->fconf.xrendersize / sprite.distance;
	sprite.init = round(a->fconf.yrendersize / 2.0 - sprite.stature / 2);
	sprite.end = round(a->fconf.yrendersize / 2.0 + sprite.stature / 2);
	return (sprite);
}

/*
** Var "midangle" is the angle of the ray that across the center
** of the sprite. It helps to calc the space to paint this sprite.
** To calc value of the mid angle, use phytagoras
** tan(alpha) = opposite / adyacent
*/

static t_sprite	calc_midangle(t_cub3d *a, t_sprite sprite)
{
	double	opposite;
	double	adyacent;

	opposite = ((int)a->rayc.yray + 0.5) - a->rayc.yplyr;
	adyacent = ((int)a->rayc.xray + 0.5) - a->rayc.xplyr;
	sprite.midangle = atan2(opposite, adyacent);
	return (sprite);
}

/*
** This function is executed only the first time that
** the sprite was found by the raycast.
*/

static t_sprite	init_sprite(t_cub3d *a, t_sprite sprite)
{
	sprite.view = true;
	sprite.xpos = (int)a->rayc.yray;
	sprite.ypos = (int)a->rayc.xray;
	sprite.buff[a->rayc.nbr_ray].ray = true;
	sprite = calc_distance_nd_stature(a, sprite);
	sprite.width_span = (a->mlibx.xpmwall[4].width * sprite.stature)
		/ a->mlibx.xpmwall[4].height;
	sprite = calc_midangle(a, sprite);
	sprite.ystep = 1.0 * a->mlibx.xpmwall[4].height / sprite.stature;
	sprite.xstep = 1.0 * a->mlibx.xpmwall[4].width / sprite.width_span;
	sprite.sequence = a->fconf.map.nbr_sprite;
	return (sprite);
}

/*
** When raycast found a sprite before wall call this function.
** This ft checks if this sprite was found before or not,
** because the next steps depends on it.
** Some data only saved first time a sprite was found, and
** other data are saved (in this function) all the times that
** the sprite was found.
*/

void			found_sprite(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c < a->fconf.map.nbr_sprite)
	{
		if (a->sprite[c].xpos == (int)a->rayc.yray
			&& a->sprite[c].ypos == (int)a->rayc.xray)
		{
			a->sprite[c].buff[a->rayc.nbr_ray].ray = true;
			return ;
		}
		c++;
	}
	allocate_sprite(a);
	a->sprite[a->fconf.map.nbr_sprite] =
		init_sprite(a, a->sprite[a->fconf.map.nbr_sprite]);
	a->fconf.map.nbr_sprite++;
}
