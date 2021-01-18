/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_calcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:21:00 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/18 03:19:05 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			clean_sprites(t_cub3d *a)
{
	int	c;

	c = 0;
	while (c <= a->fconf.map.num_sprites)
	{
		ft_memset(&a->sprite[c], '\0', sizeof(t_sprite));
		c++;
	}
	a->fconf.map.nbr_sprite = 0;
}

void			calc_init_ray(t_cub3d *a, int c)
{
	int		ray;
	double	initang;
	double	diffang;

	ray = -a->sprite[c].width_span;
	while (ray <= a->fconf.xrendersize + a->sprite[c].width_span)
	{
		initang = (a->rayc.dirplyr - a->rayc.fov / 2.0)
				+ (ray * (a->rayc.fov / a->fconf.xrendersize));
		diffang = initang - a->sprite[c].midangle;
		diffang = ft_normangle(diffang);
		if (diffang < 0.0)
			a->sprite[c].midray = ray;
		else
			break ;
		ray++;
	}
	a->sprite[c].rayinit = a->sprite[c].midray - (a->sprite[c].width_span / 2);
	a->sprite[c].rayend = a->sprite[c].midray + (a->sprite[c].width_span / 2);
}
