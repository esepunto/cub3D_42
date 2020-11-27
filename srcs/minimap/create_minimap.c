/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:53:11 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/27 14:48:00 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	draw_player(t_cub3d *a)
{
//	printf("xplayer: %f\n", a->rayc.xpos);
//	printf("yplayer: %f\n", a->rayc.ypos);
	int r = 2; // radius
	int		ox;
	int		oy;

	ox = a->minimap.sizecell * (a->rayc.xpos - (a->fconf.final_line_params + 1)) + (a->minimap.sizecell / 2);
	oy = a->rayc.ypos * a->minimap.sizecell + (a->minimap.sizecell / 2);
	for (int x = -r; x < r ; x++)
	{
		int height = (int)sqrt(r * r - x * x);
		for (int y = -height; y < height; y++)
			mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, y + oy, x + ox, 0x00FF0000);
	}
}

void	put_pixel_minimap(int x, int y, t_cub3d *a, long color)
{
	int		xmin;
	int		ymin;
	int		xmax;
	int		ymax;
	int		i;
	int		j;
	
	xmin = a->minimap.sizecell * (x - (a->fconf.final_line_params + 1));
	xmax = xmin + a->minimap.sizecell;
	ymin = a->minimap.sizecell * y;
	ymax = ymin + a->minimap.sizecell;
	
	i = xmin;
	while (i++ < xmax)
	{
		j = ymin;
		while (j++ < ymax)
			mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, j, i, color);
	}
}

int		draw_minimap(t_cub3d *a)
{
	int		x = a->fconf.final_line_params + 1;
	size_t		y = 0;
	
	a->minimap.sizecell = (a->fconf.xrendersize) / (2 * (a->fconf.map.col - (a->fconf.final_line_params + 1)));
	while (x < a->fconf.map.row)
	{
		y = 0;
		while (y <= a->fconf.map.col && a->fconf.map.maze[x][y] != '\0')
		{
			if (a->fconf.map.maze[x][y] != '1')
				put_pixel_minimap(x, y, a, 0x00000000);
			else
				put_pixel_minimap(x, y, a, 0x00FFFFFF);
			y++;
		}
		x++;
	}
	draw_player(a);
	return (0);
}

