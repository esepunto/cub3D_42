/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:41:53 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/15 14:53:10 by ssacrist         ###   ########.fr       */
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
	a->mlibx.north.img = mlx_xpm_file_to_image(a->mlibx.mlx,
				a->fconf.wall_texture[0],&a->mlibx.north.img_width,
				&a->mlibx.north.img_height);
	a->mlibx.south.img = mlx_xpm_file_to_image(a->mlibx.mlx,
				a->fconf.wall_texture[1], &a->mlibx.south.img_width,
				&a->mlibx.south.img_height);
	a->mlibx.west.img = mlx_xpm_file_to_image(a->mlibx.mlx,
				a->fconf.wall_texture[2], &a->mlibx.west.img_width,
				&a->mlibx.west.img_height);
	a->mlibx.east.img = mlx_xpm_file_to_image(a->mlibx.mlx,
				a->fconf.wall_texture[3], &a->mlibx.east.img_width,
				&a->mlibx.east.img_height);
	print_textures(a);
}

void	calc_texturing(t_cub3d *a)
{
//	int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
										// texNum is the value of the current map square minus 1
										// Indica qué textura debemos usar

//	//calculate value of wallX 
//	double wallX; //where exactly the wall was hit >>> a->rayc.xwallhit
	if (a->rayc.xhit == 1)
		a->rayc.xwallhit = a->rayc.xplyr + a->rayc.distance * a->rayc.ystep;
	else if (a->rayc.yhit == 1)
		a->rayc.xwallhit = a->rayc.xplyr + a->rayc.distance * a->rayc.xstep;
	a->rayc.xwallhit -= floor(a->rayc.xwallhit);

	//x coordinate on the texture;  texX  == a->rayc.xtexture
	a->rayc.xtexture = (int)(a->rayc.xwallhit * (double)(a->mlibx.south.img_width));//Revisar a qué textura corresponde
	if(a->rayc.xhit == 1 && a->rayc.xstep > 0)
		a->rayc.xtexture = a->mlibx.south.img_width - a->rayc.xtexture - 1;
	if(a->rayc.yhit == 1 && a->rayc.ystep < 0)
		a->rayc.xtexture = a->mlibx.south.img_width - a->rayc.xtexture - 1;


		// How much to increase the texture coordinate per screen pixel
//	double step = 1.0 * texHeight / lineHeight;
	a->rayc.steptexture = 1.0 + a->mlibx.south.img_height / 1;
	
	// Starting texture coordinate
	a->rayc.texPos = (a->rayc.initwall - (a->fconf.yrendersize / 2) + (1 / 2)) * a->rayc.steptexture;
	for(int y = a->rayc.initwall; y < a->rayc.endwall; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		a->rayc.ytexture = (int)a->rayc.texPos & (a->mlibx.south.img_height - 1);
		a->rayc.texPos += a->rayc.steptexture;
//		a->rayc.wallcolor = a->mlibx.img.addr + (a->mlibx.south.img_height * a->rayc.ytexture + a->rayc.xtexture);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//		if(a->rayc.yhit == 1)
//			a->rayc.wallcolor = (a->rayc.wallcolor >> 1) & 8355711;
		brushstroke(a, a->rayc.nbr_ray, y, a->rayc.wallcolor);
	}
}

