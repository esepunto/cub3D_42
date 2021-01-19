/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:23:45 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 19:14:37 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int			close_window(t_cub3d *a)
{
	mlx_destroy_window(a->mlibx.mlx, a->mlibx.win);
	system("leaks cub3D");
	exit(0);
}

/*
** The image should be rescaled when the resolution indicated in the
** config file is greater than the screen resolution.
** When rescaling the image, the proportions must be maintained.
** Rescaling MUST NOT be done when the "--save" argument has been included,
** as the bmp must be saved with the resolution indicated in the config file.
*/

static void	rescale_screen(t_cub3d *a)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(a->mlibx.mlx, &sizex, &sizey);
	if (sizex && sizey)
	{
		if (sizex < a->fconf.xrendersize && sizey >= a->fconf.yrendersize)
		{
			a->fconf.yrendersize = a->fconf.yrendersize
					* sizex / a->fconf.xrendersize;
			a->fconf.xrendersize = sizex;
		}
		else if (sizey < a->fconf.yrendersize)
		{
			a->fconf.xrendersize = a->fconf.xrendersize
					* sizey / a->fconf.yrendersize;
			a->fconf.yrendersize = sizey;
		}
	}
}

static int	ft_key_hit(int keycode, t_cub3d *a)
{
	a->rayc.keycode[keycode] = 1;
	return (0);
}

static int	ft_key_release(int keycode, t_cub3d *a)
{
	a->rayc.keycode[keycode] = 0;
	return (0);
}

void		init_window(t_cub3d *a)
{
	a->mlibx.mlx = mlx_init();
	if (a->save_bmp == false)
		rescale_screen(a);
	a->mlibx.img.img = mlx_new_image(a->mlibx.mlx, a->fconf.xrendersize,
			a->fconf.yrendersize);
	a->mlibx.img.addr = mlx_get_data_addr(a->mlibx.img.img,
			&a->mlibx.img.bits_per_pixel, &a->mlibx.img.line_length,
			&a->mlibx.img.endian);
	a->mlibx.win = mlx_new_window(a->mlibx.mlx, a->fconf.xrendersize,
			a->fconf.yrendersize, "cub3D");
	save_textures(a);
	throw_rays(a);
	if (a->save_bmp == true)
		take_photo(a);
	mlx_hook(a->mlibx.win, 17, 1L << 17, close_window, a);
	mlx_hook(a->mlibx.win, KEYPRESS, KEYPRESSMASK, ft_key_hit, a);
	mlx_hook(a->mlibx.win, KEYRELEASE, KEYRELEASEMASK, ft_key_release, a);
	mlx_loop_hook(a->mlibx.mlx, &caress_key, a);
	mlx_loop(a->mlibx.mlx);
}
