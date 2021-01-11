/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:34:51 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/12 00:05:15 by ssacrist         ###   ########.fr       */
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

void	spr_calc_palette(t_cub3d *a, t_sprite sprite)
{
	sprite.ysprite = (int)sprite.yfloat
		& (a->mlibx.xpmwall[4].height - 1);
	sprite.xsprite = (int)sprite.xfloat
		& (a->mlibx.xpmwall[4].width - 1);
	sprite.palette = a->mlibx.xpmwall[4].addr[
		a->mlibx.xpmwall[4].height
		* sprite.ysprite
		+ sprite.xsprite];
	if ((sprite.palette & 0x00FFFFFF) != 0)
	{
		spr_brushstroke(sprite.current_ray,
			sprite.point,
			a,
			sprite.palette);
	}
}

void	paint_spr(t_cub3d *a, int c, t_sprite sprite)
{
//	if (a->mlibx.sprite[c].distance < 0.0)
//		return ;
	sprite.current_ray = sprite.rayinit;
	sprite.xfloat = 0;
	while (sprite.current_ray <= sprite.last_ray)
	{
		sprite.yfloat = 0;
		sprite.point = sprite.init;
		while (sprite.point < sprite.end)
		{
			if (sprite.rays_used[a->mlibx.sprite[c].current_ray].ray)
				if (sprite.rays_used[sprite.current_ray].ray == true)
					spr_calc_palette(a, sprite);
//			else
//				break ;
			sprite.yfloat += sprite.ystep;
			sprite.point++;
		}
		sprite.xfloat += sprite.xstep;
		sprite.current_ray++;
	}
}

void	calc_init_ray(t_cub3d *a, int c)
{
	int	ray;

	ray = a->mlibx.sprite[c].first_ray;
	while (a->mlibx.sprite[c].rays_used[ray].angle
			< a->mlibx.sprite[c].midangle)
	{
		a->mlibx.sprite[c].rayinit = ray;
		ray++;
	}
	a->mlibx.sprite[c].rayinit++;
	a->mlibx.sprite[c].rayinit -= (a->mlibx.sprite[c].width_span / 2);
}

void	paintsprites(t_cub3d *a)
{
	int	c;

	sort_sprites(a);
	c = a->fconf.map.num_sprites - 1;
	while (c >= 0)
	{
		if (a->mlibx.sprite[c].view == false)
			c--;
		calc_init_ray(a, c);
		paint_spr(a, c, a->mlibx.sprite[c]);
		if (a->mlibx.sprite[c].buffer)
			free(a->mlibx.sprite[c].buffer);
		if (a->mlibx.sprite[c].rays_used)
			free(a->mlibx.sprite[c].rays_used);
		if (a->mlibx.sprite[c].ximpacts)
			free(a->mlibx.sprite[c].ximpacts);
		c--;
	}
}
