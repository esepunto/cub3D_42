/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonuses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:39:17 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/21 19:48:15 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	isdead(t_cub3d *a)
{
	static int	t = 0;

	if (t++ <= 50)
	{
		if (t < 10)
			mlx_string_put(a->mlibx.mlx, a->mlibx.win, 50, 60, 0x000000,
				"GAME OVER - This window will selfdestruct in 5 seconds");
		else if (t < 20)
			mlx_string_put(a->mlibx.mlx, a->mlibx.win, 50, 60, 0x000000,
				"GAME OVER - This window will selfdestruct in 4 seconds");
		else if (t < 30)
			mlx_string_put(a->mlibx.mlx, a->mlibx.win, 50, 60, 0x000000,
				"GAME OVER - This window will selfdestruct in 3 seconds");
		else if (t < 40)
			mlx_string_put(a->mlibx.mlx, a->mlibx.win, 50, 60, 0x000000,
				"GAME OVER - This window will selfdestruct in 2 seconds");
		else if (t < 50)
			mlx_string_put(a->mlibx.mlx, a->mlibx.win, 50, 60, 0x000000,
				"GAME OVER - This window will selfdestruct in 1 seconds");
	}
	else
		close_window(a);
}

void		print_lifepoints(t_cub3d *a)
{
	char	*text_life;
	char	*points;

	if (a->life <= 0)
		isdead(a);
	else
	{
		points = ft_itoa(a->life);
		text_life = ft_strjoin("Life points: ", points);
		free(points);
		mlx_string_put(a->mlibx.mlx, a->mlibx.win, 50, 50, 0x000000, text_life);
		free(text_life);
	}
}

int			shadow_color(double dist, int palette)
{
	double	dark;
	int		c[3];
	int		dc[3];
	int		rtn;
	int		z;

	dark = (2.5 / dist);
	c[0] = (palette >> 16) & 255;
	c[1] = (palette >> 8) & 255;
	c[2] = palette & 255;
	z = 0;
	while (z <= 3)
	{
		dc[z] = (int)(c[z] * dark);
		if (dc[z] > c[z])
			dc[z] = c[z];
		z++;
	}
	rtn = (dc[0] * 256 * 256) + (dc[1] * 256) + dc[2];
	return (rtn);
}
