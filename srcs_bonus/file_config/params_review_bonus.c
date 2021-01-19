/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_review_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:35 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 22:49:12 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
** Next 3 functions check the number of params in:
** 		a) walls and sprites
** 		b) floor and ceilling
** 		c) resolution
*/

static void	review_walls(int c, t_cub3d *a)
{
	int	fd;

	if (ft_cntwrds(a->fconf.wall_texture[c]) != 1)
		msg_err("Too much information in walls.");
	if (ft_chekext(a->fconf.wall_texture[c], ".png") != 0
			&& ft_chekext(a->fconf.wall_texture[c], ".xpm") != 0)
		msg_err("Bad extension in textures.");
	if ((fd = open(a->fconf.wall_texture[c], O_RDONLY)) == -1)
		msg_err("This file is out of the air.");
	else
		close(fd);
}

static void	review_cefl(int c, t_cub3d *a)
{
	if (ft_countchr(a->fconf.wall_texture[c], ',') != 2)
		msg_err("Review RGB colors. Are U in COMMA?");
	extract_rgb(c, a);
	check_rgb(c, a);
	a->fconf.ceilcolor = ceilfloorcolor(0, a);
	a->fconf.floorcolor = ceilfloorcolor(1, a);
}

static void	review_res(int c, t_cub3d *a)
{
	int		count;
	char	**size;

	if (ft_cntwrds(a->fconf.wall_texture[c]) != 2)
		msg_err("Bad information in resolution.");
	size = ft_split(a->fconf.wall_texture[c], ' ');
	count = 0;
	while (count <= 1)
	{
		size[count] = ft_delinitendblanks(size[count]);
		if (size[count] == '\0')
			msg_err("Not resolution");
		isdigit_str(size[count]);
		if (count == 0)
			a->fconf.xrendersize = ft_atoi(size[count]);
		else if (count == 1)
			a->fconf.yrendersize = ft_atoi(size[count]);
		count++;
	}
	ft_delmatrix(size);
	if (a->fconf.xrendersize == 0 || a->fconf.yrendersize == 0)
		msg_err("Review the resolution,, please.");
}

/*
**  Check if the parameters meet the stipulated requirements.
**  _______________________________
**  |  char *id | c |   element   |
**  |___________|___|_____________|
**  |	"NO"    | 0 |    north    |
**  |	"SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**  |	"EA"    | 3 |    east     |
**  |	"S1"     | 4 |   sprite1   |
**  	"S2"	  5?	  sprite2
**  |	"R"     | 6 |  resolution |
**  |	"C"     | 7 |  ceilling   |
**  |	"F"     | 8 |    floor    |
**  |___________|___|_____________|
*/

void		review_params(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c <= 8)
	{
		if (c < 6)
			review_walls(c, a);
		if (c >= 7 && c <= 8)
			review_cefl(c, a);
		if (c == 6)
			review_res(c, a);
		c++;
	}
}
