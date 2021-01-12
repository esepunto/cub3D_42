/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/12 01:10:25 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void		clean_sprites(t_cub3d *a)
{
	int	c;

	c = 0;
	while (c <= a->fconf.map.nbr_sprite)
	{
		ft_memset(&a->sprite[c], '\0', sizeof(t_sprite));
		c++;
	}
	a->fconf.map.nbr_sprite = 0;
}

void		resort(t_cub3d *a)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	j = 0;
	while (i < a->fconf.map.nbr_sprite)
	{
		j = 0;
		while (j < a->fconf.map.nbr_sprite)
		{
			if (a->sprite[j].sequence > a->sprite[i].sequence)
			{
				temp = a->sprite[j];
				a->sprite[j] = a->sprite[i];
				a->sprite[i] = temp;
				j = 0;
			}
			j++;
		}
		i++;
	}
}

void		sort_sprites(t_cub3d *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < a->fconf.map.nbr_sprite)
	{
		j = 0;
		while (j < a->fconf.map.nbr_sprite)
		{
			if (a->sprite[j].distance
					< a->sprite[i].distance
					&& a->sprite[j].sequence
					> a->sprite[i].sequence)
			{
				ft_swap(&a->sprite[j].sequence,
						&a->sprite[i].sequence);
				i = 0;
			}
			j++;
		}
		i++;
	}
	resort(a);
}

t_sprite	calc_distance_nd_stature(t_cub3d *a, t_sprite sprite)
{
	sprite.distance = hypot(
				((int)a->rayc.xray + 0.5) - a->rayc.xplyr,
				((int)a->rayc.yray + 0.5) - a->rayc.yplyr);
//	sprite.distance = sprite.distance
//				* cos(a->rayc.anglray - a->rayc.dirplyr);
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

t_sprite	calc_midangle(t_cub3d *a, t_sprite sprite)
{
	double	opposite;
	double	adyacent;

	opposite = ((int)a->rayc.yray + 0.5) - a->rayc.yplyr;
	adyacent = ((int)a->rayc.xray + 0.5) - a->rayc.xplyr;
	sprite.midangle = atan2(opposite, adyacent);
	return (sprite);
}

static void	allocate_sprite(t_cub3d *a)
{
	if (!(a->sprite[a->fconf.map.nbr_sprite].buffer =
			calloc(sizeof(a->sprite[a->fconf.map.nbr_sprite].buffer),
			a->fconf.xrendersize * sizeof(t_dist))))
		msg_err("No memory for buffer!");
	if (!(a->sprite[a->fconf.map.nbr_sprite].rays_used =
			calloc(sizeof(a->sprite[a->fconf.map.nbr_sprite].rays_used),
			a->fconf.xrendersize * sizeof(t_rays))))
		msg_err("No memory for buffer!");
	if (!(a->sprite[a->fconf.map.nbr_sprite].ximpacts =
			calloc(sizeof(a->sprite[a->fconf.map.nbr_sprite].ximpacts),
			a->fconf.xrendersize * sizeof(t_hits))))
		msg_err("No memory for buffer!");
}

/*
** This function is executed only the first time that
** the sprite was found by the raycast.
*/

static void	init_sprite(t_cub3d *a)
{
	t_sprite	sprite;

	allocate_sprite(a);
	sprite = a->sprite[a->fconf.map.nbr_sprite];
	sprite.view = true;
	sprite.xpos = (int)a->rayc.yray;
	sprite.ypos = (int)a->rayc.xray;
	sprite.rays_used[a->rayc.nbr_ray].angle = a->rayc.anglray;
	sprite.first_ray = a->rayc.nbr_ray;
	sprite.rays_used[a->rayc.nbr_ray].ray = true;
	sprite = calc_distance_nd_stature(a, sprite);
	sprite.width_span = (a->mlibx.xpmwall[4].width * sprite.stature)
		/ a->mlibx.xpmwall[4].height;
	sprite = calc_midangle(a, sprite);
	sprite.buffer[a->fconf.map.nbr_sprite].dist = sprite.distance;
	sprite.ystep = 1.0 * a->mlibx.xpmwall[4].height / sprite.stature;
	sprite.xstep = 1.0 * a->mlibx.xpmwall[4].width / sprite.width_span;
	sprite.sequence = a->fconf.map.nbr_sprite;
	a->sprite[a->fconf.map.nbr_sprite] = sprite;
}

/*
** When raycast found a sprite before wall call this function.
** This ft checks if this sprite was found before or not, 
** because the next steps depends on it.
** Some data only saved first time a sprite was found, and
** other data are saved (in this function) all the times that
** the sprite was found.
*/

void		found_sprite(t_cub3d *a)
{
	int		c;
	double	dist;

	c = 0;
	while (c < a->fconf.map.nbr_sprite)
	{
		if (a->sprite[c].xpos == (int)a->rayc.yray
			&& a->sprite[c].ypos == (int)a->rayc.xray)
		{
			a->sprite[c].last_ray = a->rayc.nbr_ray;
			dist = a->sprite[c].distance;
			dist = dist * cos(a->rayc.anglray - a->rayc.dirplyr);
			a->sprite[c].buffer[a->rayc.nbr_ray].dist = dist;
			a->sprite[c].rays_used[a->rayc.nbr_ray].angle =
				a->rayc.anglray;
			a->sprite[c].rays_used[a->rayc.nbr_ray].ray = true;
			if (a->rayc.anglray < a->sprite[c].midangle)
				a->sprite[c].midangle_minus = a->rayc.nbr_ray;
			return ;
		}
		c++;
	}
	init_sprite(a);
	a->fconf.map.nbr_sprite++;
}
