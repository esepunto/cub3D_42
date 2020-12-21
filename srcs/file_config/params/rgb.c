/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:30:23 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/21 11:41:40 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void		check_nbr(int c, t_cub3d *a)
{
	if (a->fconf.red[c - 5] < 0 || a->fconf.red[c - 5] > 255
		|| a->fconf.green[c - 5] < 0 || a->fconf.green[c - 5] > 255
		|| a->fconf.blue[c - 5] < 0 || a->fconf.blue[c - 5] > 255)
	{
		msg_err("The RGB < 0 or RGB > 255. You 're over the rainbow.");
	}
}

void		isdigit_str(char *nbr)
{
	while (*nbr)
	{
		if (ft_isdigit(*nbr) == 0)
			msg_err("Ooops. Is there a letter in number (res/rgb)?");
		nbr++;
	}
}

//uint32_t	ceilfloorcolor(int c, t_cub3d *a)
int	ceilfloorcolor(int c, t_cub3d *a)
{
	int	r;
	int g;
	int	b;

	r = a->fconf.red[c];
	g = a->fconf.green[c];
	b = a->fconf.blue[c];
	return (ft_hex2int(ft_rgb2hex(r, g, b)));
}

void		extract_rgb(int c, t_cub3d *a)
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
			a->fconf.red[c - 5] = ft_atoi(aux);
		else if (count == 1)
			a->fconf.green[c - 5] = ft_atoi(aux);
		else if (count == 2)
			a->fconf.blue[c - 5] = ft_atoi(aux);
		count++;
	}
	ft_delmatrix(color);
}
