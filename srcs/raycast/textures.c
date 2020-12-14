/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 08:41:53 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/14 09:39:28 by ssacrist         ###   ########.fr       */
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
	while(++c <= 3)
	{
		if (!a->mlibx.north.img)
			a->mlibx.north.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.north.img_width, &a->mlibx.north.img_height);
		else if (!a->mlibx.south.img)
			a->mlibx.south.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.south.img_width, &a->mlibx.south.img_height);
		else if (!a->mlibx.west.img)
			a->mlibx.west.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.west.img_width, &a->mlibx.west.img_height);
		else if (!a->mlibx.east.img)
			a->mlibx.east.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.east.img_width, &a->mlibx.east.img_height);
	}
	print_textures(a);
}

/*
void	save_textures_png(t_cub3d *a)
{
	int	c;
	
	c = -1;
	while(++c <= 3)
	{
		if (!a->mlibx.north.img)
			a->mlibx.north.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.north.img_width, &a->mlibx.north.img_height);
		else if (!a->mlibx.south.img)
			a->mlibx.south.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.south.img_width, &a->mlibx.south.img_height);
		else if (!a->mlibx.west.img)
			a->mlibx.west.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.west.img_width, &a->mlibx.west.img_height);
		else if (!a->mlibx.east.img)
			a->mlibx.east.img = mlx_xpm_file_to_image(a->mlibx.mlx, a->fconf.wall_texture[c], &a->mlibx.east.img_width, &a->mlibx.east.img_height);
	}
	print_textures(a);
}
*/

/*
mlx = mlx_init();
    win = mlx_new_window(mlx, 500, 500, "buenorra's window to put image on");
    relative_path = "./samples_xpm/event_main.xpm";
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 10, 80);
    mlx_destroy_image(mlx, img);


    relative_path = "./samples_xpm/test.xpm";
    while (c < 150)
    {
        img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
*/
