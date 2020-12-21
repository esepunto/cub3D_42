/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:41:53 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/21 16:14:55 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Textures are saved in the char** a->fconf.wall_texture[0 to 3]. fconf is a
**    struct by type t_config. 
**  _______________________________
**  |  char *id | c |   element   |
**  |___________|___|_____________|
**  |	"NO"    | 0 |    north    |
**  |	"SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**  |	"EA"    | 3 |    east     |
**  |___________|___|_____________|
**
**  This functions save the .xpm as a image at struct t_data img
**
**  If textures exist are checked previously at review_params.c
*/

void	save_textures(t_cub3d *a)
{
	int	c;
	
	c = -1;
	while (++c <= 3)
	{
		a->mlibx.xpmwall[c].relative_path = a->fconf.wall_texture[c];
		a->mlibx.xpmwall[c].img = mlx_xpm_file_to_image
				(a->mlibx.mlx,
				a->mlibx.xpmwall[c].relative_path,
				&a->mlibx.xpmwall[c].img_width,
				&a->mlibx.xpmwall[c].img_height);
		a->mlibx.xpmwall[c].addr = (int*)mlx_get_data_addr
				(a->mlibx.xpmwall[c].img,
				&a->mlibx.xpmwall[c].bits_per_pixel,
				&a->mlibx.xpmwall[c].line_length,
				&a->mlibx.xpmwall[c].endian);
	}
//	print_textures(a);
//	print_addr(a);
}

void	calc_texturing(t_cub3d *a)
{
	if (a->rayc.xhit == 1)
		a->rayc.xwallhit = a->rayc.yray;
	
	else if (a->rayc.yhit == 1)
		a->rayc.xwallhit = a->rayc.xray;
	
	a->rayc.xwallhit -= floor(a->rayc.xwallhit);
	
 	a->rayc.xtexture = (a->rayc.xwallhit
			* a->mlibx.xpmwall[a->rayc.wall].img_width) / 1; 
	
/*	a->rayc.xtexture = (int)(a->rayc.xwallhit
			* (double)a->mlibx.xpmwall[a->rayc.wall].img_width);*/
	
	if ((a->rayc.xhit == 1 && a->rayc.xstep < 0)
			|| (a->rayc.yhit == 1 && a->rayc.quadrant < 3))
	{
		a->rayc.xtexture =
			a->mlibx.xpmwall[a->rayc.wall].img_width - 1 - a->rayc.xtexture;
	}
	
	a->rayc.ysteptexture = 1.0 * a->mlibx.xpmwall[a->rayc.wall].img_height
			/ a->rayc.staturewall;
	
	a->rayc.ytexturefloat = a->rayc.ysteptexture *
			(a->rayc.initwall + a->rayc.staturewall / 2
			- a->fconf.yrendersize / 2);
}
