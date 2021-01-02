/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/02 16:40:04 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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

void	spr_calc_step(t_cub3d *a)
{
	t_sprite	sprite;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	if (cos(a->rayc.anglray) >= 0.0)
		sprite.xstep = ceil(cos(a->rayc.anglray));
	else
		sprite.xstep = floor(cos(a->rayc.anglray));
	if (sin(a->rayc.anglray) >= 0.0)
		sprite.ystep = ceil(sin(a->rayc.anglray));
	else
		sprite.ystep = floor(sin(a->rayc.anglray));
	sprite.angle = a->rayc.anglray;
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}

void	calc_quadrantsprite(t_cub3d *a)
{
	t_sprite	sprite;
	double		val;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	val = fmod(a->rayc.anglray, M_PI * 2);
	if ((val >= 0 && val < M_PI_2) || (val >= -(M_PI * 2) && val < -M_PI_2 * 3))
		sprite.quadrant = 1;
	else if ((val >= M_PI_2 && val < M_PI) || (val >= -(M_PI_2 * 3) && val < -M_PI))
		sprite.quadrant = 2;
	else if ((val >= M_PI && val < M_PI_2 * 3) || (val >= -M_PI && val < -M_PI_2))
		sprite.quadrant = 3;
	else if ((val >= M_PI_2 * 3 && val < M_PI * 2) || (val >= -M_PI_2 && val < -0))
		sprite.quadrant = 4;
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
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
	sprite.x = (sprite.xspritehit * a->mlibx.xpmwall[4].width) / 1;
	if ((sprite.xhit == 1 && sprite.xstep < 0)//xtep??
			|| (sprite.yhit == 1 && sprite.quadrant < 3))
	{
		sprite.x = a->mlibx.xpmwall[4].width - 1 - sprite.x;
	}
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}

static void	init_sprite(t_cub3d *a)
{
	t_sprite	sprite;
	
	
	
	spr_calc_step(a);
	calc_quadrantsprite(a);
	calc_spriteimpact(a);

	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	
	sprite.xpos = (int)a->rayc.yray;
	sprite.ypos = (int)a->rayc.xray;
	
	sprite.dist2hit = hypot(a->rayc.xray - a->rayc.xplyr, a->rayc.yray - a->rayc.yplyr);
	sprite.dist2add = (- cos(a->rayc.anglray)) * sprite.xspritehit;
	sprite.distance = sprite.dist2hit + sprite.dist2add;
	sprite.distance = sprite.distance * cos(a->rayc.anglray - a->rayc.dirplyr);
	
	sprite.stature = a->fconf.xrendersize / a->rayc.distance;
	sprite.init = (round(a->fconf.yrendersize / 2.0 - sprite.stature / 2));
	sprite.end = (round(a->fconf.yrendersize / 2.0 + sprite.stature / 2));
	
	sprite.ystep = 1.0 * a->mlibx.xpmwall[4].height / sprite.stature;
	sprite.yfloat = sprite.ystep * (sprite.init + sprite.stature / 2
			- a->fconf.yrendersize / 2);
	
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
//	print_sprites(a);
	a->mlibx.nbr_sprite++;
}
