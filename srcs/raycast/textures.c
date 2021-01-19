/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:41:53 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 04:51:08 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Textures are saved in the char** a->fconf.wall_texture[0 to 3]. fconf is a
**    struct by type t_config.
**  _______________________________
**  |  char *id | c |   element   |
**  |___________|___|_____________|
**  |   "NO"    | 0 |    north    |
**  |   "SO"    | 1 |    south    |
**  |   "WE"    | 2 |    west     |
**  |   "EA"    | 3 |    east     |
**  |   "S"     | 4 |   sprites   |
**  |___________|___|_____________|
**  This functions save the .xpm as a image at struct t_data img
**
**  If textures exist are checked previously at review_params.c
*/

static void	save_sprite(t_cub3d *a)
{
	a->mlibx.object.relative_path = a->fconf.wall_texture[4];
	a->mlibx.object.img =
				mlx_xpm_file_to_image(a->mlibx.mlx,
				a->mlibx.object.relative_path,
				&a->mlibx.object.width,
				&a->mlibx.object.height);
	a->mlibx.object.addr =
				(int*)mlx_get_data_addr(a->mlibx.object.img,
				&a->mlibx.object.bits_per_pixel,
				&a->mlibx.object.line_length,
				&a->mlibx.object.endian);
}

void		save_textures(t_cub3d *a)
{
	static int	c = -1;

	if (c != -1)
		return ;
	while (++c <= 3)
	{
		a->mlibx.xpmwall[c].relative_path = a->fconf.wall_texture[c];
		a->mlibx.xpmwall[c].img =
				mlx_xpm_file_to_image(a->mlibx.mlx,
				a->mlibx.xpmwall[c].relative_path,
				&a->mlibx.xpmwall[c].width,
				&a->mlibx.xpmwall[c].height);
		a->mlibx.xpmwall[c].addr =
				(int*)mlx_get_data_addr(a->mlibx.xpmwall[c].img,
				&a->mlibx.xpmwall[c].bits_per_pixel,
				&a->mlibx.xpmwall[c].line_length,
				&a->mlibx.xpmwall[c].endian);
	}
	save_sprite(a);
}

/*
** To draw the walls, an image (texture) is chosen for
** each orientation that is predefined in the configuration file.
**
** With the help of the minilibx, a one-dimensional matrix is extracted
** from each texture that includes the color of each texture pixel, and the
** width and height of the texture measured in pixels.
**
** With this information, the algorithm will calculate the x-coordinate of
** the wall where the ray has hit, and will draw a line on that coordinate
** throughout the window.
**
** ++++ Texture algorithm ++++
** 1. Calculates the x-coordinate of the wall where the lightning struck.
** 2. Round the coordinate down.
** 3. Multiply the coordinate by the width in pixels of the texture.
** 4. Adjusts the value obtained to prevent the image from flipping sideways.
** After calculating the x-coordinate of the vertical line to draw,
** calculates what color each pixel should print based on the texture.
** 5. It calculates the variable ysteptexture, which indicates how many
** pixels of the wall correspond to each pixel of the texture.
** 6. Calculate the y-coordinate by multiplying the ysteptexture variable by
** the highest point of the wall, plus half the height of the wall, minus
** half the height of the window. Believe me, it runs :)
*/

void		calc_texturing(t_cub3d *a)
{
	if (a->rayc.xhit == 1)
		a->rayc.xwallhit = a->rayc.yray;
	else if (a->rayc.yhit == 1)
		a->rayc.xwallhit = a->rayc.xray;
	a->rayc.xwallhit -= floor(a->rayc.xwallhit);
	a->rayc.xtexture = (a->rayc.xwallhit
			* a->mlibx.xpmwall[a->rayc.wall].width) / 1;
	if ((a->rayc.xhit == 1 && a->rayc.xstep < 0)
			|| (a->rayc.yhit == 1 && a->rayc.quadrant < 3))
	{
		a->rayc.xtexture =
			a->mlibx.xpmwall[a->rayc.wall].width - 1 - a->rayc.xtexture;
	}
	a->rayc.ysteptexture = 1.0 * a->mlibx.xpmwall[a->rayc.wall].height
			/ a->rayc.staturewall;
	a->rayc.ytexturefloat = 0;
}
