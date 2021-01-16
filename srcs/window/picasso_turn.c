/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso_turn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/16 20:38:16 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Functions to print sprites
*/

static void	spr_calc_palette(t_cub3d *a, int c)
{
	a->sprite[c].ysprite = (int)a->sprite[c].yfloat
		& (a->mlibx.xpmwall[4].height - 1);
	a->sprite[c].xsprite = (int)a->sprite[c].xfloat
		& (a->mlibx.xpmwall[4].width - 1);
	a->sprite[c].palette = a->mlibx.xpmwall[4].addr[
		a->mlibx.xpmwall[4].height
		* a->sprite[c].ysprite
		+ a->sprite[c].xsprite];
	if ((a->sprite[c].palette & 0x00FFFFFF) != 0)
		brushstroke(a->sprite[c].current_ray, a->sprite[c].point, a,
			a->sprite[c].palette);
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
				spr_calc_palette(a, c);
				a->sprite[c].yfloat += a->sprite[c].ystep;
				a->sprite[c].point++;
			}
		}
		a->sprite[c].xfloat += a->sprite[c].xstep;
		a->sprite[c].current_ray++;
	}
}

static void	resort(t_cub3d *a)
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

static void	sort_sprites(t_cub3d *a)
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
		if (a->sprite[c].distance >= 0.6)
			paint_spr(a, c);
		if (a->sprite[c].buff)
			free(a->sprite[c].buff);
	}
}
