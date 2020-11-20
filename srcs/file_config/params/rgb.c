/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:30:23 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/20 13:16:48 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	check_nbr(int c, t_cub3d *a)
{
	if (a->fconf.red[c] < 0 || a->fconf.red[c] > 255
		|| a->fconf.green[c] < 0 || a->fconf.green[c] > 255
		|| a->fconf.blue[c] < 0 || a->fconf.blue[c] > 255)
	{
		msg_err("RGB < 0 or RGB > 255");
	}
}

void	isdigit_str(char *color)
{
	while (*color)
	{
		if (ft_isdigit(*color) == 0)
			msg_err("Ooops. Please, review the numbers (res/rgb).");
		color++;
	}
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
		aux = ft_strtrim((const char *)color[count], " ");
		if (aux == '\0')
			msg_err("Not RGB colors");
		isdigit_str(aux);
		if (count == 0)
			a->fconf.red[c] = ft_atoi(aux);
		else if (count == 1)
			a->fconf.green[c] = ft_atoi(aux);
		else if (count == 2)
			a->fconf.blue[c] = ft_atoi(aux);
		free(aux);
		count++;
	}
	ft_delmatrix(color);
}
