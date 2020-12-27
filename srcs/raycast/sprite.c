/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/27 02:32:09 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sprite(t_cub3d *a)
{
	a->rayc.alldistances[a->rayc.nbr_ray] = a->rayc.distance;
//	print_distances(a);
}

void	found_sprite(t_cub3d *a)
{
	int	c;
	
	if (a->mlibx.nbr_sprite == 0)
	{
		if (!(a->mlibx.sprite =
			ft_calloc(a->fconf.map.col * a->fconf.map.nbrlines, sizeof(t_texture))))
		msg_err("WTF! Give me back my memory!");
	}
	c = a->mlibx.nbr_sprite;
	if (a->mlibx.nbr_sprite == 0 || (a->mlibx.sprite[c].xpos != (int)a->rayc.yray
			&& a->mlibx.sprite[c].ypos != (int)a->rayc.xray))
	{
		c = a->mlibx.nbr_sprite;
		a->mlibx.sprite[c].relative_path = a->fconf.wall_texture[7];
		a->mlibx.sprite[c].img =
				mlx_xpm_file_to_image(a->mlibx.mlx,
				a->mlibx.sprite[c].relative_path,
				&a->mlibx.sprite[c].width,
				&a->mlibx.sprite[c].height);
		a->mlibx.sprite[c].addr =
				(int*)mlx_get_data_addr(a->mlibx.sprite[c].img,
				&a->mlibx.sprite[c].bits_per_pixel,
				&a->mlibx.sprite[c].line_length,
				&a->mlibx.sprite[c].endian);
		a->mlibx.sprite[c].xpos = (int)a->rayc.yray;
		a->mlibx.sprite[c].ypos = (int)a->rayc.xray;
		a->mlibx.nbr_sprite++;
	}
}
