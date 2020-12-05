/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vangoghs_turn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:27:24 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/05 08:57:13 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	brushstroke(t_cub3d *a, int x, int y, int color)
{
	char	*dst;

	dst = a->mlibx.img.addr + (y * a->mlibx.img.line_length + x * (a->mlibx.img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	pointillism(t_cub3d *a)
{
	double point;
	
	point = 0;
	while (point < a->fconf.yrendersize)
	{
		if (point < a->rayc.initwall)
			brushstroke(a, a->rayc.nbr_ray, point, a->fconf.ceilcolor);
		else if (point < a->rayc.endwall)
			brushstroke(a, a->rayc.nbr_ray, point, a->rayc.wallcolor);
		else
			brushstroke(a, a->rayc.nbr_ray, point, a->fconf.floorcolor);
		point++;
	}
}
