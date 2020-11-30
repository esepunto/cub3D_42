/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delmem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:25:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/30 19:36:55 by ssacrist         ###   ########.fr       */
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

void print_struct(t_cub3d *a)
{
	printf("key: %d\n", a->rayc.keycode);
	printf("xrendersize: %d\n", a->fconf.xrendersize);
	printf("yrendersize: %d\n", a->fconf.yrendersize);
	printf("ray: %d\n", a->rayc.ray);
	printf("xpos: %f - ", a->rayc.xpos);
	printf("ypos: %f\n", a->rayc.ypos);
	printf("xdir: %f - ", a->rayc.xdir);
	printf("ydir: %f\n", a->rayc.ydir);
	printf("xcamera: %f\n", a->rayc.xcamera);
	printf("xmap: %d - ", a->rayc.xmap);
	printf("ymap: %d\n", a->rayc.ymap);
	printf("xplane: %f - ", a->rayc.xplane);
	printf("yplane: %f\n", a->rayc.yplane);
	printf("xraydir: %f - ", a->rayc.xraydir);
	printf("yraydir: %f\n", a->rayc.yraydir);
	printf("xsidedist: %f - ", a->rayc.xsidedist);
	printf("ysidedist: %f\n", a->rayc.ysidedist);
	printf("xdeltadist: %f - ", a->rayc.xdeltadist);
	printf("ydeltadist: %f\n", a->rayc.ydeltadist);
	printf("perpwalldist: %f\n\n", a->rayc.perpwalldist);
}

void	print_fconfig(t_cub3d *a)
{
	int	i;

	i = 0;
	printf("row: %d\n", a->fconf.map.row);
	printf("colum: %zu\n", a->fconf.map.col);
//	printf("map[0][7] = %c\n", a->fconf.map.maze[0][7]);
	while (i <= a->fconf.map.row)
	{
		printf("linea %d: %s\n", i, a->fconf.map.maze[i]);
		i++;
	}
//	printf("map[0][0] = %c", a->fconf.map.maze[0][0]);
/*	printf("\n|%s|\n", a->fconf.wallno);
	printf("|%s|\n", a->fconf.wallso);
	printf("|%s|\n", a->fconf.wallwe);
	printf("|%s|\n", a->fconf.wallea);
	printf("|%s|\n", a->fconf.res);
	printf("|%s|\n", a->fconf.ceil);
	printf("|%s|\n", a->fconf.flr);
	printf("|%s|\n", a->fconf.sprite);
	printf("TEXTURE: |%s|\n", a->fconf.wallno_texture);
	printf("TEXTURE: |%s|\n", a->fconf.wallso_texture);
	printf("TEXTURE: |%s|\n", a->fconf.wallwe_texture);
	printf("TEXTURE: |%s|\n", a->fconf.wallea_texture);
	printf("TEXTURE: |%s|\n", a->fconf.sprite_texture);
*/	i= 0;
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

