/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/16 03:48:01 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	spr_calc_palette(t_cub3d *a, int c)
{
	a->sprite[c].ysprite = (int)a->sprite[c].yfloat
		& (a->mlibx.xpmwall[4].height - 1);
	a->sprite[c].xsprite = (int)a->sprite[c].xfloat
		& (a->mlibx.xpmwall[4].width - 1);
//	a->sprite[c].palette = 0xFF00FF;
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
	if (a->sprite[c].distance < 0.6)
		return ;
	a->sprite[c].current_ray = a->sprite[c].rayinit;
	a->sprite[c].xfloat = 0;
	while (a->sprite[c].current_ray <= a->sprite[c].rayend
		&& a->sprite[c].current_ray < a->fconf.xrendersize)
	{
//		printf("ray[%d]: %d\n", a->sprite[c].current_ray, a->sprite[c].buff[a->sprite[c].current_ray].ray);
		
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

static void	calc_init_ray(t_cub3d *a, int c)
{
	int		ray;
	double	ang;
	double	diffang;
	
	ray = - (a->sprite[c].width_span);
//	printf("midangle[%d]: %f\n", c, a->sprite[c].midangle);
	while (ray <= a->fconf.xrendersize + a->sprite[c].width_span)
	{
		
		ang = (a->rayc.dirplyr - a->rayc.fov / 2.0)
				+ (ray * (a->rayc.fov / a->fconf.xrendersize));
/*		
		if (ray >= 0)
			ang = a->rayc.angbuf[ray];
		else
*///	ang = a->rayc.angbuf[0] + (ray * (a->rayc.fov / a->fconf.xrendersize));
	//	ang = a->rayc.angbuf[0] + (ray * (a->rayc.fov / a->fconf.xrendersize));
		
//		printf("ang[%d]: %f\n", ray, ang);
		diffang = ang - a->sprite[c].midangle;
		if (diffang < - 1.0 * M_PI)
			diffang += 2.0 * M_PI;
		if (diffang > M_PI)
			diffang -= 2.0 * M_PI;
		if (diffang < 0.0)
			a->sprite[c].midray = ray;
		else
			break ;
		ray++;
	}
	a->sprite[c].rayinit = a->sprite[c].midray - (a->sprite[c].width_span / 2);
	a->sprite[c].rayend = a->sprite[c].midray + (a->sprite[c].width_span / 2);
/*	printf("initangle[%d]: %f\n", c, a->sprite[c].initangle);
	printf(" endangle[%d]: %f\n", c, a->sprite[c].endangle);
	printf(" rayinit[%d]: %d\n", c, a->sprite[c].rayinit);
	printf("  rayend[%d]: %d\n", c, a->sprite[c].rayend);
	printf("  raymid[%d]: %d\n\n", c, a->sprite[c].midray);*/
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
		paint_spr(a, c);
		if (a->sprite[c].buff)
			free(a->sprite[c].buff);
	}
}
