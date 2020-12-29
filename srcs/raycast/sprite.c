/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/29 04:01:04 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clean_sprites(t_cub3d *a)
{
	int	c;
		
	c = 0;
	while (c <= a->mlibx.nbr_sprite)
	{
		ft_memset(&a->mlibx.sprite[c], '\0', sizeof(t_sprite));
		c++;
	}
	a->mlibx.nbr_sprite = 0;
}

void	save_sprites(t_cub3d *a)
{
	static int	c = -1;

	if (c != -1)
		return ;
	while (++c < a->fconf.map.num_sprites)
	{
		a->mlibx.sprite[c].relative_path = a->fconf.wall_texture[4];
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
	}
}

void	allocate_sprites(t_cub3d *a)
{
	int	c;
	
	c = 0;
	if (!(a->mlibx.sprite =
			ft_calloc(a->fconf.map.num_sprites, sizeof(t_sprite))))
		msg_err("WTF! Give me back my memory!");
/*	while (c < a->fconf.map.num_sprites)
	{
		if (!(a->mlibx.sprite[c].dist_sprite = ft_calloc(a->fconf.xrendersize, sizeof(double))))
			msg_err("WTF! Give me back my memory!");
		c++;
	}*/
}

void	if_newsprite(t_cub3d *a)
{
	int	c;
	
	c = 0;
	while (c < a->mlibx.nbr_sprite)
	{
		if (a->mlibx.sprite[c].xpos == (int)a->rayc.yray
			&& a->mlibx.sprite[c].ypos == (int)a->rayc.xray)
		{
//			a->mlibx.sprite[a->mlibx.nbr_sprite].dist_sprite[a->rayc.nbr_ray] = 8.0;
			return ;
		}
		c++;
	}
	a->mlibx.sprite[a->mlibx.nbr_sprite].xpos = (int)a->rayc.yray;
	a->mlibx.sprite[a->mlibx.nbr_sprite].ypos = (int)a->rayc.xray;
	
	a->mlibx.nbr_sprite++;
}

void	found_sprite(t_cub3d *a)
{
//	a->mlibx.sprite[a->mlibx.nbr_sprite].dist_sprite[a->rayc.nbr_ray] = a->rayc.distance;
	
	if_newsprite(a);
//	a->mlibx.sprite[a->mlibx.nbr_sprite].dist_sprite[a->rayc.nbr_ray] = 8.0;
//				hypot(a->rayc.xray - a->rayc.xplyr,
//					a->rayc.yray - a->rayc.yplyr)
//				* cos(a->rayc.anglray - a->rayc.dirplyr);
}
