/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/02 13:38:53 by ssacrist         ###   ########.fr       */
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
	t_sprite	sprite;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	
	if ((int)a->rayc.xray != (int)(a->rayc.xray - a->rayc.xincrease))
		sprite.xhit = 1;
	else
		sprite.xhit = 0;
	if ((int)a->rayc.yray != (int)(a->rayc.yray - a->rayc.yincrease))
		sprite.yhit = 1;
	else
		sprite.yhit = 0;

	if (sprite.xhit == 1)
		sprite.xspritehit = a->rayc.yray;
	else if (sprite.yhit == 1)
		sprite.xspritehit = a->rayc.xray;
	sprite.xspritehit -= floor(sprite.xspritehit);

	sprite.x = (sprite.xspritehit * a->mlibx.sprite[a->rayc.wall].width) / 1;
	if ((sprite.xhit == 1 && a->rayc.xstep < 0)
			|| (sprite.yhit == 1 && sprite.quadrant < 3))
	{
		sprite.x = sprite.width - 1 - sprite.x;
	}
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}

/*
void	calc_quadrantsprite(t_cub3d *a)
{
	double	val;
	t_sprite	sprite;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];

	val = fmod(a->rayc.anglray, M_PI * 2);
	if ((val >= 0 && val < M_PI_2) || (val >= -(M_PI * 2) && val < -M_PI_2 * 3))
		sprite.quadrant = 1;
	if ((val >= M_PI_2 && val < M_PI) || (val >= -(M_PI_2 * 3) && val < -M_PI))
		sprite.quadrant = 2;
	if ((val >= M_PI && val < M_PI_2 * 3) || (val >= -M_PI && val < -M_PI_2))
		sprite.quadrant = 3;
	if ((val >= M_PI_2 * 3 && val < M_PI * 2) || (val >= -M_PI_2 && val < -0))
		sprite.quadrant = 4;
	
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}
*/

static void	init_sprite(t_cub3d *a)
{
	t_sprite	sprite;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	
	calc_spriteimpact(a);
//	calc_quadrantsprite(a);
	
	sprite.xpos = (int)a->rayc.yray;
	sprite.ypos = (int)a->rayc.xray;
	sprite.xfloat = a->rayc.xray;
	
//	sprite.yauxfloat = a->rayc.yray;
	sprite.ystep = 1.0 * sprite.height / sprite.stature;
	sprite.yfloat = sprite.ystep * (sprite.init + sprite.stature / 2
			- a->fconf.yrendersize / 2);	

	sprite.dist2hit =
		hypot(a->rayc.xray - a->rayc.xplyr, a->rayc.yray - a->rayc.yplyr)
		* cos(a->rayc.anglray - a->rayc.dirplyr);
	sprite.dist2add = (- cos(a->rayc.anglray)) * sprite.xspritehit;
	sprite.distance = sprite.dist2hit + sprite.dist2add;
	
	sprite.stature = a->fconf.xrendersize / a->rayc.distance;//REVISAR!! Puede que haya que conectarlo con altura píxeles de pared.
	sprite.init = (round(a->fconf.yrendersize / 2.0 - sprite.stature / 2));
	sprite.end = (round(a->fconf.yrendersize / 2.0 + sprite.stature / 2));
	
	sprite.angle = a->rayc.anglray - a->rayc.dirplyr;//Ojo, esto puede que no me sirva y solo necesite el ángulo tal cual, sin restar.
	sprite.sequence = a->mlibx.nbr_sprite;

	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
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
