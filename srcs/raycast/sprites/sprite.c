/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/08 16:10:46 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	clean_sprites(t_cub3d *a)
{
	int	c;
		
	c = 0;
	while (c <= a->mlibx.nbr_sprite)
	{
		ft_memset(&a->mlibx.sprite[c], '\0', sizeof(t_sprite));
		c++;
	}
	a->mlibx.nbr_sprite = 0;
}

void	resort(t_cub3d *a)
{
	int			i;
	int			j;
	t_sprite	temp;
	
	i = 0;
	j = 0;
	while (i < a->mlibx.nbr_sprite)
	{
		j = 0;
		while (j < a->mlibx.nbr_sprite)
		{
			if (a->mlibx.sprite[j].sequence > a->mlibx.sprite[i].sequence)
			{
				temp = a->mlibx.sprite[j];
				a->mlibx.sprite[j] = a->mlibx.sprite[i];
				a->mlibx.sprite[i] = temp;
				j = 0;
			}
			j++;
		}
		i++;
	}
}

void 	sort_sprites(t_cub3d *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < a->mlibx.nbr_sprite)
	{
		j = 0;
		while (j < a->mlibx.nbr_sprite)
		{
			if (a->mlibx.sprite[j].distance < a->mlibx.sprite[i].distance
					&& a->mlibx.sprite[j].sequence > a->mlibx.sprite[i].sequence)
			{
				ft_swap(&a->mlibx.sprite[j].sequence, &a->mlibx.sprite[i].sequence);
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
	sprite.init = (round(a->fconf.yrendersize / 2.0 - sprite.stature / 2));
	sprite.end = (round(a->fconf.yrendersize / 2.0 + sprite.stature / 2));
//	sprite.init = (int)((float)(a->fconf.yrendersize) / 2.0 - sprite.stature / 2);
//	sprite.end = (int)((float)(a->fconf.yrendersize) / 2.0 + sprite.stature / 2);
	return (sprite);
}

/*
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
	if (!(a->mlibx.sprite[a->mlibx.nbr_sprite].buffer =
			calloc(sizeof(a->mlibx.sprite[a->mlibx.nbr_sprite].buffer),
			a->fconf.xrendersize * sizeof(t_dist))))
		msg_err("No memory for buffer!");
	if (!(a->mlibx.sprite[a->mlibx.nbr_sprite].rays_used =
			calloc(sizeof(a->mlibx.sprite[a->mlibx.nbr_sprite].rays_used),
			a->fconf.xrendersize * sizeof(t_rays))))
		msg_err("No memory for buffer!");
	if (!(a->mlibx.sprite[a->mlibx.nbr_sprite].ximpacts =
			calloc(sizeof(a->mlibx.sprite[a->mlibx.nbr_sprite].ximpacts),
			a->fconf.xrendersize * sizeof(t_hits))))
		msg_err("No memory for buffer!");
}

static void	init_sprite(t_cub3d *a)
{
	t_sprite	sprite;

	allocate_sprite(a);
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	sprite.xpos = (int)a->rayc.yray;
	sprite.ypos = (int)a->rayc.xray;
	sprite.rays_used[a->rayc.nbr_ray].ray = true;
	sprite = calc_distance_nd_stature(a, sprite);
	
//	sprite.width_span = (a->mlibx.xpmwall[4].width * sprite.stature) / a->mlibx.xpmwall[4].height;
	
	sprite = calc_midangle(a, sprite);

	sprite.buffer[a->mlibx.nbr_sprite].dist = sprite.distance;
	
	sprite.ystep = 1.0 * a->mlibx.xpmwall[4].height / sprite.stature;
	sprite.yfloat = sprite.ystep * (sprite.init + sprite.stature / 2
		- a->fconf.yrendersize / 2);

//	sprite.xstep = 1.0 * a->mlibx.xpmwall[4].width / sprite.width_span;//step = stature / a->mlibx.xpmwall[4].width REVISAR
//	sprite.xfloat = sprite.xstep;// * (rayo_actual - rayo medio);REVISAR
	
	
	sprite.sequence = a->mlibx.nbr_sprite;
	sprite.first_ray = a->rayc.nbr_ray;
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
//	print_sprites(a);
}

void	found_sprite(t_cub3d *a)
{
	int		c;
	double	dist;
	
	c = 0;
	while (c < a->mlibx.nbr_sprite)
	{
		if (a->mlibx.sprite[c].xpos == (int)a->rayc.yray
			&& a->mlibx.sprite[c].ypos == (int)a->rayc.xray)
			{
				a->mlibx.sprite[c].last_ray = a->rayc.nbr_ray;
				dist = a->mlibx.sprite[c].distance;
				dist = dist * cos(a->rayc.anglray - a->rayc.dirplyr);
				a->mlibx.sprite[c].buffer[a->rayc.nbr_ray].dist = dist;
				a->mlibx.sprite[c].rays_used[a->rayc.nbr_ray].angle = a->rayc.anglray;
				a->mlibx.sprite[c].rays_used[a->rayc.nbr_ray].ray = true;
				a->mlibx.sprite[c].ximpacts[a->rayc.nbr_ray].ximpact = a->rayc.xtexture;
				a->mlibx.sprite[c] = calc_midangle(a, a->mlibx.sprite[c]);
				return ;
			}
		c++;
	}
	init_sprite(a);
	a->mlibx.nbr_sprite++;
}








