/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:53:11 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/30 14:30:29 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	draw_line(t_cub3d *a, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX;
	double deltaY;
	int pixels;
	double pixelX;
	double pixelY;

	deltaX = endX - beginX; // 10
	deltaY = endY - beginY; // 0
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY)); // 10
//	pixels ^ 2 = (deltaX ^ 2) + (deltaY ^ 2) >>> pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10
	pixelX = beginX; // 640
	pixelY = beginY; // 360
	deltaX /= pixels; // 1 >>> 10 / 10
	deltaY /= pixels; // 0 >>>  0 / 10
	while (pixels)
	{
		mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void	draw_player(t_cub3d *a)
{
	int r = 4; // radius
	int		ox;
	int		oy;
	int sizecell = a->minimap.sizecell;

	ox = a->rayc.xpos * sizecell;
	oy = (a->rayc.ypos - a->fconf.map.first_line) * sizecell;
	for (int x = -r; x < r ; x++)
	{
		int height = (int)sqrt(r * r - x * x);
		for (int y = -height; y < height; y++)
			mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, x + ox, y + oy, 0x00FF0000);
	}
	draw_line(a, ox, oy, ox + (a->rayc.xdir * 40), oy + (a->rayc.ydir * 40), 0x00FF00FF);
}

void	put_pixel_minimap(int j, int i, t_cub3d *a, long color)
{
	double		xmin;
	double		ymin;
	double		xmax;
	double		ymax;
		
	a->minimap.sizecell = a->fconf.yrendersize / (a->fconf.map.row - a->fconf.map.first_line);
	xmin = a->minimap.sizecell * j;
	xmax = xmin + a->minimap.sizecell;
	ymin = a->minimap.sizecell * (i - a->fconf.map.first_line);
	ymax = ymin + a->minimap.sizecell;
	i = ymin;
	while (i < ymax)
	{
		j = xmin;
		while (j < xmax)
		{
			mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cub3d *a)
{
	int		i = a->fconf.map.first_line;
	size_t	j = 0;
	
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j <= a->fconf.map.col && a->fconf.map.maze[i][j] != '\0')
		{
			if (a->fconf.map.maze[i][j] == '1')
				put_pixel_minimap(j, i, a, 0x00000000);
			else
				put_pixel_minimap(j, i, a, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	draw_player(a);
}

