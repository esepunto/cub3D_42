/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/28 04:24:35 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sprite(t_cub3d *a)
{
	a->rayc.alldistances[a->rayc.nbr_ray] = a->rayc.distance;
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
	if (!(a->mlibx.sprite =
			ft_calloc(a->fconf.map.num_sprites, sizeof(t_sprite))))
		msg_err("WTF! Give me back my memory!");
}

void	found_sprite(t_cub3d *a)
{
	save_sprites(a);
	if (a->mlibx.nbr_sprite == 0)
	{
		a->mlibx.sprite[a->mlibx.nbr_sprite].xpos = (int)a->rayc.yray;
		a->mlibx.sprite[a->mlibx.nbr_sprite].ypos = (int)a->rayc.xray;
		a->mlibx.nbr_sprite++;
	}

	else if (a->mlibx.sprite[a->mlibx.nbr_sprite - 1].xpos
				!= (int)a->rayc.yray
			|| a->mlibx.sprite[a->mlibx.nbr_sprite - 1].ypos
				!= (int)a->rayc.xray)
	{
		a->mlibx.sprite[a->mlibx.nbr_sprite].xpos = (int)a->rayc.yray;
		a->mlibx.sprite[a->mlibx.nbr_sprite].ypos = (int)a->rayc.xray;
		print_sprites(a);
		a->mlibx.nbr_sprite++;
	}
//	print_sprites(a);
}
