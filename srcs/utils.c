/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:25:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/14 09:23:56 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	delmem(t_cub3d *a)
{
	if (a)
	{
		init_struct(a);
		if (sizeof(a->fconf.wall_texture) >= 848)
			ft_delmatrix(a->fconf.wall_texture);
		if (sizeof(a->fconf.map.maze) >= 208)
			ft_delmatrix(a->fconf.map.maze);
		if (sizeof(a) >= sizeof(t_cub3d))
			free(a);
	}
}

int		msg_err(char *error)
{
	ft_printf("Error\n%s\n\n", error);
	system("leaks cub3D");
	exit(0);
}

void	print_struct(t_cub3d *a)
{

	printf("xrendersize: %d\n", a->fconf.xrendersize);
	printf("yrendersize: %d\n", a->fconf.yrendersize);
	printf("angulo FOV: |%f|\n", a->rayc.fov);
	printf("color ceil: |%x|\n", a->fconf.ceilcolor);
	printf("color floor: |%x|\n\n", a->fconf.floorcolor);
}

void	print_textures(t_cub3d *a)
{
	printf("north: %s - width %d - heigth %d\n", a->fconf.wall_texture[0], a->mlibx.north.img_width, a->mlibx.north.img_height);
	printf("south: %s - width %d - heigth %d\n", a->fconf.wall_texture[1], a->mlibx.south.img_width, a->mlibx.south.img_height);
	printf("west: %s - width %d - heigth %d\n", a->fconf.wall_texture[2], a->mlibx.west.img_width, a->mlibx.west.img_height);
	printf("east: %s - width %d - heigth %d\n", a->fconf.wall_texture[3], a->mlibx.east.img_width, a->mlibx.east.img_height);
}

void	print_fconfig(t_cub3d *a)
{
	int	i;

	i = 0;
	printf("row: %d\n", a->fconf.map.row);
	printf("colum: %zu\n", a->fconf.map.col);
	while (i <= a->fconf.map.row)
	{
		printf("linea %d: %s\n", i, a->fconf.map.maze[i]);
		i++;
	}
	i = 0;
	while (i <= 7 && a->fconf.wall_texture[i])
	{
		printf("TEXTURE[%d]:  |%s|\n", i, a->fconf.wall_texture[i]);
		i++;
	}
	printf("Last line with params: %d\n", a->fconf.final_line_params);
	printf("First line of map: %d\n", a->fconf.map.first_line);
	printf("final row: %d\n", a->fconf.map.row);
	printf("nº players: %d\n", a->fconf.map.num_players);
	i = 5;
	printf("Red[%d]: |%d|, Green[%d]: |%d| Blue[%d]: |%d|\n", i, a->fconf.red[i], i, a->fconf.green[i], i, a->fconf.blue[i]);
	i = 6;
	printf("Red[%d]: |%d|, Green[%d]: |%d| Blue[%d]: |%d|\n", i, a->fconf.red[i], i, a->fconf.green[i], i, a->fconf.blue[i]);
	printf("resX: %d\n", a->fconf.xrendersize);
	printf("resY: %d\n", a->fconf.yrendersize);
	printf("\n********** FIN IMPRESION ***********\n\n\n\n\n\n");
}
