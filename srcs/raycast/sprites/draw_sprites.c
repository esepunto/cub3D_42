/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/07 22:38:44 by ssacrist         ###   ########.fr       */
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
	a->mlibx.sprite[c].ysprite = (int)a->mlibx.sprite[c].yfloat
		& (a->mlibx.xpmwall[4].height - 1);
//	a->mlibx.sprite[c].palette = 923333;
//	print_addr(a);
	a->mlibx.sprite[c].palette = a->mlibx.xpmwall[4].addr
		[a->mlibx.xpmwall[4].height
		* a->mlibx.sprite[c].ysprite + a->mlibx.sprite[c].xsprite];
	if ((a->mlibx.sprite[c].palette & 0x00FFFFFF) != 0)
		spr_brushstroke(a->mlibx.sprite[c].current_ray, a->mlibx.sprite[c].point, a, a->mlibx.sprite[c].palette);
}

void	paint_spr(t_cub3d *a, int c)
{
	a->mlibx.sprite[c].current_ray = a->mlibx.sprite[c].first_ray;
	
	while (a->mlibx.sprite[c].current_ray <= a->mlibx.sprite[c].last_ray)
	{
		a->mlibx.sprite[c].point = a->mlibx.sprite[c].init;
		while (a->mlibx.sprite[c].point < a->mlibx.sprite[c].end)
		{
			if (a->mlibx.sprite[c].rays_used[a->mlibx.sprite[c].current_ray].ray == 1)
				spr_calc_palette(a, c);
			a->mlibx.sprite[c].yfloat += a->mlibx.sprite[c].ystep;//La madre del cordero.
			a->mlibx.sprite[c].point++;
		}
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
		print_sprites(a);
		paint_spr(a, c);
		if (a->mlibx.sprite[c].buffer)
			free(a->mlibx.sprite[c].buffer);
		if (a->mlibx.sprite[c].rays_used)
			free(a->mlibx.sprite[c].rays_used);
		if (a->mlibx.sprite[c].ximpacts)
			free(a->mlibx.sprite[c].ximpacts);
	}
}
