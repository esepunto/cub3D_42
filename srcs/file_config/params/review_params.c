/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:35 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 11:06:56 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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
	a->fconf.wall_texture[c] = ft_delendblanks(a->fconf.wall_texture[c]);
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

char	*replacetabs(char *str)
{
	size_t	c;
	
	c = 0;
	while(c <= ft_strlen(str))
	{
		if (str[c] == '	')
			str[c] = ' ';
		c++;
	}
	return (str);
}

void	review_res(int c, t_cub3d *a)
{
	int		count;
	char	**size;
	char	*aux;

	if (ft_cntwrds(a->fconf.wall_texture[c]) != 2)
		msg_err("Poor information in resolution.");
	a->fconf.wall_texture[c] = replacetabs(a->fconf.wall_texture[c]);
	size = ft_split(a->fconf.wall_texture[c], ' ');
	count = 0;
	while (count <= 1)
	{
		if (!size[count])
			msg_err("Bad nbr param resolution");
		aux = ft_delinitendblanks(size[count]);
		if (aux == '\0')
			msg_err("Not resolution");
		isdigit_str(aux);
		if (count == 0)
			a->fconf.xrendersize = ft_atoi(aux);
		else if (count == 1)
			a->fconf.yrendersize = ft_atoi(aux);
		count++;
	}
	ft_delmatrix(size);
}

void	review_params(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c <= 7)
	{
//		printf("texture: |%s|\n", a->fconf.wall_texture[c]);
		if (c < 4 || c == 7)
			review_walls(c, a);
		if (c >= 5 && c <= 6)
			review_cefl(c, a);
		if (c == 4)
		{
			review_res(c, a);
			if (a->fconf.xrendersize == 0 || a->fconf.yrendersize == 0)
				msg_err("Review the resolution,, please.");
		}
		c++;
	}
}
