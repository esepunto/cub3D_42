/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/13 00:15:29 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	spr_calc_palette(t_cub3d *a, int c)
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

void	paint_spr(t_cub3d *a, int c)
{
	if (a->sprite[c].distance < 0.0)
		return ;
	a->sprite[c].current_ray = a->sprite[c].rayinit;
	a->sprite[c].xfloat = 0;
	while (a->sprite[c].current_ray <= a->sprite[c].last_ray)
	{
		a->sprite[c].yfloat = 0;
		a->sprite[c].point = a->sprite[c].init;
		while (a->sprite[c].point < a->sprite[c].end)
		{
			if (a->sprite[c].buff[a->sprite[c].current_ray].ray != '\0')
			{
				if (a->sprite[c].buff[a->sprite[c].current_ray].ray == true)
					spr_calc_palette(a, c);
			}
			else
				break ;
			a->sprite[c].yfloat += a->sprite[c].ystep;
			a->sprite[c].point++;
		}
		a->sprite[c].xfloat += a->sprite[c].xstep;
		a->sprite[c].current_ray++;
	}
}

void	calc_init_ray(t_cub3d *a, int c)
{
	int	ray;

	ray = a->sprite[c].first_ray;
	while (a->sprite[c].buff[ray].angle
			< a->sprite[c].midangle)
	{
		a->sprite[c].midray = ray;
		ray++;
	}
	a->sprite[c].midray++;
	a->sprite[c].rayinit = a->sprite[c].midray - (a->sprite[c].width_span / 2);
}

void	paintsprites(t_cub3d *a)
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
