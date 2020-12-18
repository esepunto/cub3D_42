/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/18 10:18:26 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	brushstroke(t_cub3d *a, int x, int y, int color)
{
	char	*dst;

	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length
			+ x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
while (i < f->ml.drawstart)
	{
		*(f->ml.frame.data + (i * f->w) + f->ml.x) = f->c_c;
		i++;
	}
*/

/*
		a->mlibx.xpmwall[c].img = mlx_xpm_file_to_image(a->mlibx.mlx,
				a->fconf.wall_texture[c],&a->mlibx.xpmwall[c].img_width,
				&a->mlibx.xpmwall[c].img_height);
		a->mlibx.xpmwall[c].img->addr = mlx_get_data_addr(a->mlibx.xpmwall[c].img,
			&a->mlibx.xpmwall[c].img->bits_per_pixel, &a->mlibx.xpmwall[c].img->line_length,
			&a->mlibx.xpmwall[c].img->endian);
*/


void	pointillism(t_cub3d *a)
{
	double	point;
	int		color;
	int		c;

	c = 0;
	point = 0;
	while (point < a->fconf.yrendersize)
	{
		if (point < a->rayc.initwall)
			brushstroke(a, a->rayc.nbr_ray, point, a->fconf.ceilcolor);
		else if (point < a->rayc.endwall)
		{
			a->rayc.ytexture = (int)a->rayc.texPos & (a->mlibx.xpmwall[c].img_height - 1);
			a->rayc.texPos += a->rayc.steptexture;
			color = a->mlibx.xpmwall[c].img->addr[a->mlibx.xpmwall[c].img_height * a->rayc.ytexture + a->rayc.xtexture];
//			*(f->ml.frame.data + (point * a->fconf.xrendersize) + f->ml.x) = color;
			brushstroke(a, a->rayc.nbr_ray, point, color);
		}
//			brushstroke(a, a->rayc.nbr_ray, point, a->rayc.wallcolor);
		else if (point >= a->rayc.endwall)
			brushstroke(a, a->rayc.nbr_ray, point, a->fconf.floorcolor);
		point++;
	}
}
