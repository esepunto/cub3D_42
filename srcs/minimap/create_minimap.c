/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:53:11 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/27 11:10:05 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	size_minimap(t_cub3d *a)
{
	a->minimap.sizecell = a->fconf.xrendersize / (2 * a->fconf.map.col);
}

void	put_black(int x, int t, t_cub3d *a)
{
	int		xmin;
	int		ymin;
	int		xmax;
	int		ymax;

	xmin = (a->minimap.sizecell * x);
	xmax = a->minimap.sizecell + (a->minimap.sizecell * x)
	
	while ()
	mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, a->minimap.xpix, a->minimap.ypix, 0x00000000);
}

void	put_white(t_cub3d *a)
{
	0x00FFFFFF
}

void	draw_minimap(t_cub3d *a)
{
	int		row = a->fconf.map.row;
	int		column = a->fconf.map.col;
	char	**map = a->fconf.map.maze;
	double	x = 0;
	double	y = 0;
	
	while (x <= row)
	{
		y = 0;
		while (y <= column)
		{
			if (map[x][y]) == '1')
				put_black(x, i, a);
			else
				put_white(x, i, a);
			y++;
		}
		x++;
	}
}
