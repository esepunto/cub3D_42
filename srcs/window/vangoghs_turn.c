/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/21 12:20:13 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	brushstroke(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put(t_cub3d *a, int x, int y, int color)
{
	char	*dst;

	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	pointillism(t_cub3d *a)
{
	int			point;
	int			color;

	point = 0;
	while (point < a->fconf.yrendersize)
	{
		if (point < a->rayc.initwall)
			brushstroke(&a->mlibx.img, a->rayc.nbr_ray, point, a->fconf.ceilcolor);
		else if (point < a->rayc.endwall)
		{
			color = a->mlibx.xpmwall[a->rayc.wall].img->addr[a->mlibx.xpmwall[a->rayc.wall].img_width
					* (int)a->rayc.ytexturefloat + a->rayc.xtexture];
			brushstroke(&a->mlibx.img, a->rayc.nbr_ray, point, color);
			a->rayc.ytexturefloat += a->rayc.ysteptexture;
		}
		else if (point >= a->rayc.endwall)
			brushstroke(&a->mlibx.img, a->rayc.nbr_ray, point, a->fconf.floorcolor);
		point++;
	}
}
