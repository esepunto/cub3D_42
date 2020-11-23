/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:25:17 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 13:32:59 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_fconfig(t_cub3d *a)
{
	int	i;

	i = 0;
	printf("row: %d\n", a->fconf.map.row);
	printf("colum: %zu\n", a->fconf.map.col);
//	printf("map[0][7] = %c\n", a->fconf.map.map[0][7]);
	while (i <= a->fconf.map.row)
	{
		printf("linea %d: %s\n", i, a->fconf.map.map[i]);
		i++;
	}
//	printf("map[0][0] = %c", a->fconf.map.map[0][0]);
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
