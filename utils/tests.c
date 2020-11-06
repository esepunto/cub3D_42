/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:25:17 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/06 14:27:55 by ssacrist         ###   ########.fr       */
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
	printf("\n%s\n\n", a->fconf.wallno);
	printf("%s\n\n", a->fconf.wallso);
	printf("%s\n\n", a->fconf.wallwe);
	printf("%s\n\n", a->fconf.wallea);
	printf("%s\n\n", a->fconf.res);
	printf("%s\n\n", a->fconf.ceil);
	printf("%s\n\n", a->fconf.flr);
	printf("%s\n\n", a->fconf.sprite);
}
