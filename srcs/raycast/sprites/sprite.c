/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/01 22:51:13 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	save_sprites(t_cub3d *a)
{
	static int	c = -1;

	if (c != -1)
		return ;
	while (++c < a->fconf.map.num_sprites)
	{
		a->mlibx.sprite[c].relative_path = a->fconf.wall_texture[4];
		a->mlibx.sprite[c].img =
				mlx_xpm_file_to_image(a->mlibx.mlx,
				a->mlibx.sprite[c].relative_path,
				&a->mlibx.sprite[c].width,
				&a->mlibx.sprite[c].height);
		a->mlibx.sprite[c].addr =
				(int*)mlx_get_data_addr(a->mlibx.sprite[c].img,
				&a->mlibx.sprite[c].bits_per_pixel,
				&a->mlibx.sprite[c].line_length,
				&a->mlibx.sprite[c].endian);
	}
}

void	clean_sprites(t_cub3d *a)
{
	int	c;
		
	c = 0;
	while (c <= a->mlibx.nbr_sprite)
	{
		ft_memset(&a->mlibx.sprite[c], '\0', sizeof(t_sprite));
		c++;
	}
	a->mlibx.nbr_sprite = 0;
}

void	resort(t_cub3d *a)
{
	int			i;
	int			j;
	t_sprite	temp;
	
	i = 0;
	j = 0;
	while (i < a->mlibx.nbr_sprite)
	{
		j = 0;
		while (j < a->mlibx.nbr_sprite)
		{
			if (a->mlibx.sprite[j].sequence > a->mlibx.sprite[i].sequence)
			{
				temp = a->mlibx.sprite[j];
				a->mlibx.sprite[j] = a->mlibx.sprite[i];
				a->mlibx.sprite[i] = temp;
				j = 0;
			}
			j++;
		}
		i++;
	}
}

void 	sort_sprites(t_cub3d *a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < a->mlibx.nbr_sprite)
	{
		j = 0;
		while (j < a->mlibx.nbr_sprite)
		{
			if (a->mlibx.sprite[j].dist2hit < a->mlibx.sprite[i].dist2hit
					&& a->mlibx.sprite[j].sequence > a->mlibx.sprite[i].sequence)
			{
				ft_swap(&a->mlibx.sprite[j].sequence, &a->mlibx.sprite[i].sequence);
				i = 0;
			}
			j++;
		}
		i++;
	}
	resort(a);
}

static void	calc_spriteimpact(t_cub3d *a)
{
	if ((int)a->rayc.xray != (int)(a->rayc.xray - a->rayc.xincrease))
		a->mlibx.sprite[a->mlibx.nbr_sprite].xhit = 1;
	else
		a->mlibx.sprite[a->mlibx.nbr_sprite].xhit = 0;
	if ((int)a->rayc.yray != (int)(a->rayc.yray - a->rayc.yincrease))
		a->mlibx.sprite[a->mlibx.nbr_sprite].yhit = 1;
	else
		a->mlibx.sprite[a->mlibx.nbr_sprite].yhit = 0;

	if (a->mlibx.sprite[a->mlibx.nbr_sprite].xhit == 1)
		a->mlibx.sprite[a->mlibx.nbr_sprite].xspritehit = a->rayc.yray;
	else if (a->mlibx.sprite[a->mlibx.nbr_sprite].yhit == 1)
		a->mlibx.sprite[a->mlibx.nbr_sprite].xspritehit = a->rayc.xray;
	a->mlibx.sprite[a->mlibx.nbr_sprite].xspritehit -=
				floor(a->mlibx.sprite[a->mlibx.nbr_sprite].xspritehit);
	
	
	a->mlibx.sprite[a->mlibx.nbr_sprite].x = (a->mlibx.sprite[a->mlibx.nbr_sprite].xspritehit
			* a->mlibx.sprite[a->rayc.wall].width) / 1;
	if ((a->mlibx.sprite[a->mlibx.nbr_sprite].xhit == 1 && a->rayc.xstep < 0)
			|| (a->mlibx.sprite[a->mlibx.nbr_sprite].yhit == 1 && a->mlibx.sprite[a->mlibx.nbr_sprite].quadrant < 3))
	{
		a->mlibx.sprite[a->mlibx.nbr_sprite].x =
			a->mlibx.sprite[a->mlibx.nbr_sprite].width - 1 - a->mlibx.sprite[a->mlibx.nbr_sprite].x;
	}
}

static void	calc_quadrantsprite(t_cub3d *a)//Revisar valores dados
{
	double	val;

	val = fmod(a->rayc.anglray, M_PI * 2);
	if ((val >= 0 && val < M_PI_2) || (val >= -(M_PI * 2) && val < -M_PI_2 * 3))
		a->mlibx.sprite[a->mlibx.nbr_sprite].quadrant = 1;
	if ((val >= M_PI_2 && val < M_PI) || (val >= -(M_PI_2 * 3) && val < -M_PI))
		a->mlibx.sprite[a->mlibx.nbr_sprite].quadrant = 2;
	if ((val >= M_PI && val < M_PI_2 * 3) || (val >= -M_PI && val < -M_PI_2))
		a->mlibx.sprite[a->mlibx.nbr_sprite].quadrant = 3;
	if ((val >= M_PI_2 * 3 && val < M_PI * 2) || (val >= -M_PI_2 && val < -0))
		a->mlibx.sprite[a->mlibx.nbr_sprite].quadrant = 4;
}

static void	init_sprite(t_cub3d *a)
{
	calc_spriteimpact(a);
	calc_quadrantsprite(a);
	
	a->mlibx.sprite[a->mlibx.nbr_sprite].xpos = (int)a->rayc.yray;
	a->mlibx.sprite[a->mlibx.nbr_sprite].ypos = (int)a->rayc.xray;
	a->mlibx.sprite[a->mlibx.nbr_sprite].xfloat = a->rayc.xray;
	
//	a->mlibx.sprite[a->mlibx.nbr_sprite].yauxfloat = a->rayc.yray;
	a->mlibx.sprite[a->mlibx.nbr_sprite].ystep = 1.0 * a->mlibx.sprite[a->mlibx.nbr_sprite].height
			/ a->mlibx.sprite[a->mlibx.nbr_sprite].stature;
	a->mlibx.sprite[a->mlibx.nbr_sprite].yfloat =
			a->mlibx.sprite[a->mlibx.nbr_sprite].ystep
			* (a->mlibx.sprite[a->mlibx.nbr_sprite].init
			+ a->mlibx.sprite[a->mlibx.nbr_sprite].stature / 2
			- a->fconf.yrendersize / 2);	
	
	
	a->mlibx.sprite[a->mlibx.nbr_sprite].dist2hit =
		hypot(a->rayc.xray - a->rayc.xplyr, a->rayc.yray - a->rayc.yplyr)
		* cos(a->rayc.anglray - a->rayc.dirplyr);
	a->mlibx.sprite[a->mlibx.nbr_sprite].dist2add = (- cos(a->rayc.anglray))
			* a->mlibx.sprite[a->mlibx.nbr_sprite].xspritehit;
	a->mlibx.sprite[a->mlibx.nbr_sprite].distance =
			a->mlibx.sprite[a->mlibx.nbr_sprite].dist2hit
			+ a->mlibx.sprite[a->mlibx.nbr_sprite].dist2add;
	
	
	a->mlibx.sprite[a->mlibx.nbr_sprite].stature = a->fconf.xrendersize / a->rayc.distance;//REVISAR!! Puede que haya que conectarlo con altura píxeles de pared.
	a->mlibx.sprite[a->mlibx.nbr_sprite].init = (round(a->fconf.yrendersize / 2.0
				- a->mlibx.sprite[a->mlibx.nbr_sprite].stature / 2));
	a->mlibx.sprite[a->mlibx.nbr_sprite].end = (round(a->fconf.yrendersize / 2.0
				+ a->mlibx.sprite[a->mlibx.nbr_sprite].stature / 2));
	
	
	a->mlibx.sprite[a->mlibx.nbr_sprite].angle = a->rayc.anglray - a->rayc.dirplyr;//Ojo, esto puede que no me sirva y solo necesite el ángulo tal cual, sin restar.
	a->mlibx.sprite[a->mlibx.nbr_sprite].sequence = a->mlibx.nbr_sprite;


}



void	found_sprite(t_cub3d *a)
{
	int	c;
	
	c = 0;
	while (c < a->mlibx.nbr_sprite)
	{
		if (a->mlibx.sprite[c].xpos == (int)a->rayc.yray
			&& a->mlibx.sprite[c].ypos == (int)a->rayc.xray)
			return ;
		c++;
	}
	init_sprite(a);
	a->mlibx.nbr_sprite++;
}
