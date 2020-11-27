/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:53:11 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/27 12:39:25 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

void	put_pixel_minimap(int x, int y, t_cub3d *a, long color)
{
	int		xmin;
	int		ymin;
	int		xmax;
	int		ymax;
	int		i;
	int		j;
	
	xmin = a->minimap.sizecell * (x - (a->fconf.final_line_params + 1));
	xmax = xmin + a->minimap.sizecell - 1;
	ymin = a->minimap.sizecell * y;
	ymax = ymin + a->minimap.sizecell - 1;
	
/*	printf("sizecell: |%d|\n", a->minimap.sizecell);
	printf("xmin: |%d|\n", xmin);
	printf("xmax: |%d|\n", xmax);
	printf("ymin: |%d|\n", ymin);
	printf("ymax: |%d|\n\n", ymax);
*/	i = xmin;
	while (i < xmax)
	{
		j = ymin;
		while (j < ymax)
		{
			mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, j, i, color);
//			printf("i: |%d| - j: |%d|\n", i, j);
//			exit (0);
			j++;
		}
		i++;
	}
}

int		draw_minimap(t_cub3d *a)
{
	int		row = a->fconf.map.row;
	int		column = a->fconf.map.col;
	char	**map = a->fconf.map.maze;
	int		x = a->fconf.final_line_params + 1;
	int		y = 0;
	
	a->minimap.sizecell = (a->fconf.xrendersize) / (2 * (a->fconf.map.col - (a->fconf.final_line_params + 1)));
	while (x < row)
	{
		y = 0;
		while (y <= column && map[x][y] != '\0')
		{
//			printf("x: |%d| - y: |%d| -", x, y);
//			printf("map[x][y]: |%c|\n", map[x][y]);
			if (map[x][y] != '1')
				put_pixel_minimap(x, y, a, 0x00000000);
			else
				put_pixel_minimap(x, y, a, 0x00FFFFFF);
			y++;
		}
		x++;
	}
	return (0);
}
