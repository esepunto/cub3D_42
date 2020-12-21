/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/21 07:40:34 by ssacrist         ###   ########.fr       */
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
	uint32_t	color;

//	char *dst;

	color = 0;
	point = 0;
	while (point < a->fconf.yrendersize)
	{
		if (point < a->rayc.initwall)
			brushstroke(a, a->rayc.nbr_ray, point, a->fconf.ceilcolor);
		else if (point < a->rayc.endwall)
		{

			a->rayc.ytexture = (int)a->rayc.texPos;// &(a->mlibx.xpmwall[a->rayc.wall].img_height - 1);
			a->rayc.texPos += a->rayc.ysteptexture;
//			a->rayc.texPos = fmin(64, a->rayc.texPos);//Necessary?
			color = a->mlibx.xpmwall[a->rayc.wall].img->addr[a->mlibx.xpmwall[a->rayc.wall].img_height
					* a->rayc.ytexture + a->rayc.xtexture];
			brushstroke(a, a->rayc.nbr_ray, point, color);
//			my_mlx_pixel_put(a, a->rayc.nbr_ray, point, color);
		}
		else if (point >= a->rayc.endwall)
		{
			brushstroke(a, a->rayc.nbr_ray, point, a->fconf.floorcolor);
//			dst = a->mlibx.img.addr + (point * a->mlibx.img.line_length + a->rayc.nbr_ray * (a->mlibx.img.bits_per_pixel / 8));
//			*(unsigned int*)dst = a->fconf.floorcolor;
		}
		point++;
	} 
}

/*
void			draw_textured_line(t_game *game, size_t start,
	size_t end, t_ray ray)
{
	t_texture	texture;
	size_t		i;
	int			text_y;
	int			color;

	i = start - 1;
	texture = ray.texture;
	while (++i < end)
	{
		text_y = (int)ray.texture_pos % texture.height;
		ray.texture_pos += ray.texture_step;
		if (text_y <= texture.height)
			color = texture.ptr[texture.height * text_y + ray.texture_x];
		set_pixel(game, game->width * i + game->x, color);
	}
}
*/
