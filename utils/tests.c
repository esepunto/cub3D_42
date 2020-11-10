/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:25:17 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/10 10:16:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_fconfig(t_cub3d *a)
{
	int	i;

	i = 0;
	printf("row: %d\n", a->fconf.map.row);
	printf("colum: %zu\n", a->fconf.map.col);
	printf("map[0][7] = %c\n", a->fconf.map.map[0][7]);
	while (i < a->fconf.map.row)
	{
		printf("linea %d: %s\n", i, a->fconf.map.map[i]);
		i++;
	}
	printf("map[0][0] = %c", a->fconf.map.map[0][0]);
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
	while (i <= 7)
	{
//		printf("\n       [%d]|%s|\n", i, a->fconf.wall[i]);
		printf("TEXTURE[%d]:  |%s|\n", i, a->fconf.wall_texture[i]);
		i++;
	}
	printf("\n");
}
