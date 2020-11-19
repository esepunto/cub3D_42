/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:35 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/19 14:36:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** Check if anything param is repeat ("NO", "SO", etc.)
*/

void	is_repeat(int thisline, t_cub3d *a, const char *id)
{
	int			j;
	int			z;
	int			len;

	len = ft_strlen(id);
	thisline = thisline + 1;
	while (thisline < a->fconf.map.row)
	{
		j = jump_sp(thisline, a);
		z = 0;
		while (z < len && a->fconf.map.map[thisline][j] == id[z])
		{
			if (z == len - 1)
			{
				if (a->fconf.final_line_params < thisline)
					a->fconf.final_line_params = thisline;
				msg_err("No no no no: a param is repeat.");
			}
			z++;
			j++;
		}
		thisline++;
	}
	return ;
}

/*
** Next 3 functions check the number of params in:
** 		a) walls and sprites
** 		b) floor and ceilling
** 		c) resolution
*/

void	review_walls(int c, t_cub3d *a)
{
	int	fd;

	if (ft_cntwrds(a->fconf.wall_texture[c]) != 1)
		msg_err("Too much information in walls.");
	a->fconf.wall_texture[c] = ft_lastblanks(a->fconf.wall_texture[c]);
	if (ft_chekext(a->fconf.wall_texture[c], ".png") != 0
			&& ft_chekext(a->fconf.wall_texture[c], ".xpm") != 0)
		msg_err("Bad extension in textures.");
	if ((fd = open(a->fconf.wall_texture[c], O_RDONLY)) == -1)
		msg_err("This file is out of the air.");
	else
		close(fd);
}

void	review_cefl(int c, t_cub3d *a)
{
	char	*param;

	param = a->fconf.wall_texture[c];

	if (ft_cntwrds(param) < 1 || ft_cntwrds(param) > 5)
		msg_err("Bad floor/ceilling elements.");
	if (ft_countchr(param, ',') != 2)
		msg_err("Review RGB colors. Are U in COMMA?");
	extract_rgb(c, a);
	check_nbr(c, a);
}

void	review_res(int c, t_cub3d *a)
{
	char	**size;
	char	*x;
	char	*y;

	if (ft_cntwrds(a->fconf.wall_texture[c]) != 2)
		msg_err("Poor information in resolution.");
	size = ft_split(a->fconf.wall_texture[c], ' ');
	if (!size[0] || !size[1] || size[2])
		msg_err("Bad nbr param resolution");
	x = ft_strtrim(size[0], " ");
	y = ft_strtrim(size[1], " ");
	if (x == '\0' || y == '\0')
		msg_err("Not resolution");
	isdigit_str(x);
	isdigit_str(y);
	a->fconf.xrendersize = ft_atoi(x);
	a->fconf.yrendersize = ft_atoi(y);
	free(x);
	free(y);
	ft_delmatrix(size);
	if (a->fconf.xrendersize == 0 || a->fconf.yrendersize == 0)
		msg_err("Review the resolution,, please.");

}

void	review_params(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c <= 7)
	{
		if (c < 4 || c == 7)
			review_walls(c, a);
		if (c >= 5 && c <= 6)
			review_cefl(c, a);
		if (c == 4)
			review_res(c, a);
		c++;
	}
}
