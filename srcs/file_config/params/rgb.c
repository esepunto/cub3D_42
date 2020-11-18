/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:30:23 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/18 14:45:19 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"


void	check_nbr(int c, t_cub3d *a)
{
	int	red;
	int	green;
	int	blue;

	red = a->fconf.red[c];
	green = a->fconf.green[c];
	blue = a->fconf.blue[c];
	if (red < 0 || red > 255
		|| green < 0 || green > 255
		|| blue < 0 || blue > 255)
	{
		msg_err("RGB < 0 or RGB > 255");
	}
}

void	isdigit_str(char *color)
{
	while (*color)
	{
		if (ft_isdigit(*color) == 0)
			msg_err("Review the numbers.");
		color++;
	}
}

void	extract_rgb(int c, t_cub3d *a)
{
	char	**color;
	char	*red;
	char	*green;
	char	*blue;

	color = ft_split(a->fconf.wall_texture[c], ',');
	if (!color[0] || !color[1] || !color[2])
		msg_err("Not 3 RGB colors");
	red = ft_strtrim((const char *)color[0], " ");
	green = ft_strtrim((const char *)color[1], " ");
	blue = ft_strtrim((const char *)color[2], " ");
	if (red[0] == '\0' || green[0] == '\0' || blue[0] == '\0')
		msg_err("Not 3 RGB colors");
	isdigit_str(red);
	isdigit_str(green);
	isdigit_str(blue);
	a->fconf.red[c] = ft_atoi(red);
	a->fconf.green[c] = ft_atoi(green);
	a->fconf.blue[c] = ft_atoi(blue);
	free(red);
	free(green);
	free(blue);
	ft_delmatrix(color);
}
