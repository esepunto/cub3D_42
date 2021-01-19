/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colors_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:30:23 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/20 00:04:38 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	check_rgb(int c, t_cub3d *a)
{
	if (a->fconf.red[c - 6] < 0 || a->fconf.red[c - 6] > 255
		|| a->fconf.green[c - 6] < 0 || a->fconf.green[c - 6] > 255
		|| a->fconf.blue[c - 6] < 0 || a->fconf.blue[c - 6] > 255)
	{
		msg_err("The RGB < 0 or RGB > 255. You 're over the rainbow.");
	}
}

void	isdigit_str(char *nbr)
{
	while (*nbr)
	{
		if (ft_isdigit(*nbr) == 0)
			msg_err("Ooops. Is there a letter in number (res/rgb)?");
		nbr++;
	}
}

int		ceilfloorcolor(int c, t_cub3d *a)
{
	int	r;
	int g;
	int	b;

	r = a->fconf.red[c];
	g = a->fconf.green[c];
	b = a->fconf.blue[c];
	return (ft_hex2int(ft_rgb2hex(r, g, b)));
}

void	extract_rgb(int c, t_cub3d *a)
{
	int		count;
	char	**color;
	char	*aux;

	color = ft_split(a->fconf.wall_texture[c], ',');
	count = 0;
	while (count <= 2)
	{
		if (!color[count])
			msg_err("Not RGB color");
		aux = ft_delinitendblanks(color[count]);
		if (aux == '\0')
			msg_err("Not RGB colors");
		isdigit_str(aux);
		if (count == 0)
			a->fconf.red[c - 7] = ft_atoi(aux);
		else if (count == 1)
			a->fconf.green[c - 7] = ft_atoi(aux);
		else if (count == 2)
			a->fconf.blue[c - 7] = ft_atoi(aux);
		count++;
	}
	ft_delmatrix(color);
}
