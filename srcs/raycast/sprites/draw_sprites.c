/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/04 19:05:50 by ssacrist         ###   ########.fr       */
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
	a->mlibx.sprite[c].palette = a->fconf.ceilcolor;
/*	a->mlibx.sprite[c].palette = a->mlibx.xpmwall[4].addr[
		a->mlibx.xpmwall[4].height * a->mlibx.sprite[c].y
		+ (int)a->mlibx.sprite[c].x];
*/	if((a->mlibx.sprite[c].palette & 0x00FFFFFF) != 0)
		spr_brushstroke(a->mlibx.sprite[c].current_ray, a->mlibx.sprite[c].point, a, a->mlibx.sprite[c].palette);
}


void	paint_spr(t_cub3d *a, int c)
{
	a->mlibx.sprite[c].total_rays = a->mlibx.sprite[c].last_ray - a->mlibx.sprite[c].first_ray;
	a->mlibx.sprite[c].x_aux = fmod((double)a->mlibx.sprite[c].total_rays, (double)a->mlibx.xpmwall[4].width);
//	printf("total rays: %d\n", a->mlibx.sprite[c].total_rays);
//	printf("ancho text_spr: %d\n", a->mlibx.xpmwall[4].width);
//	printf("x_aux: %f\n", a->mlibx.sprite[c].x_aux);
	a->mlibx.sprite[c].current_ray = a->mlibx.sprite[c].first_ray;
	while (a->mlibx.sprite[c].current_ray <= a->mlibx.sprite[c].last_ray)
	{
		a->mlibx.sprite[c].point = a->mlibx.sprite[c].init;
		a->mlibx.sprite[c].point = 0;
		while (a->mlibx.sprite[c].point < a->mlibx.sprite[c].end)
		{
			if (a->rayc.buffer[a->mlibx.sprite[c].current_ray].dist >
					a->mlibx.sprite[c].distance)
				spr_calc_palette(a, c);
			a->mlibx.sprite[c].yfloat += a->mlibx.sprite[c].ystep;
			a->mlibx.sprite[c].point++;
		}
		a->mlibx.sprite[c].x += a->mlibx.sprite[c].x_aux;
//		printf("x: %f\n", a->mlibx.sprite[c].x);
		a->mlibx.sprite[c].current_ray++;
	}
}

void	paintsprites(t_cub3d *a)
{
	int	c;
	
	sort_sprites(a);
	c = a->fconf.map.num_sprites;
	while (--c >= 0)
	{
		paint_spr(a, c);
		if (a->mlibx.sprite[c].buffer)
			free(a->mlibx.sprite[c].buffer);
	}
}
