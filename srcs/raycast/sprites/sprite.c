/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:50:27 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/04 13:24:26 by ssacrist         ###   ########.fr       */
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

/*
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
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}
*/

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

void	calc_lasthit(t_cub3d *a)
{
	t_sprite	sprite;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	if ((int)a->rayc.xray != (int)(a->rayc.xray - a->rayc.xincrease))
		sprite.last_xhit = 1;
	else
		sprite.last_xhit = 0;
	if ((int)a->rayc.yray != (int)(a->rayc.yray - a->rayc.yincrease))
		sprite.last_yhit = 1;
	else
		sprite.last_yhit = 0;
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}

void	calc_spriteimpact(t_cub3d *a)
{
	t_sprite	sprite;
	
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
/*	
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
	if ((sprite.xhit == 1 && sprite.xstep < 0)
			|| (sprite.yhit == 1 && sprite.quadrant < 3))
	{
		sprite.x = a->mlibx.xpmwall[4].width - 1 - sprite.x;
	}
*/
	sprite.angle = a->rayc.anglray;
	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}

/*
** https://www.universoformulas.com/matematicas/trigonometria/resolucion-triangulos/
** 
** In every triangle withs faces a, b, c and each opposite angle A, B, C,
** a/(sin A) == b /(sin B) == c / sin(C)
**
** If we know 2 angles and one side, we could calc all the sides and the angles.
**
** So: b = (a * sin(B)) / sin(A)
**     c = (a * sin(C)) / sin(A)
*/

double	calc_dist2add(t_sprite sprite)
{
	printf("pre xspritehit: %f\n", sprite.xspritehit);
	printf("pre angle: %f\n", sprite.angle);
	printf("pre d2a: %f\n", sprite.dist2add);
	printf("sum_angle: %f\n", M_PI - M_PI_4 - (M_PI_2 - sprite.angle));
	printf("quadrant: %d\n", sprite.quadrant);
	if (sprite.xhit == 1)
	{
		if (sprite.quadrant == 4)
			sprite.dist2add = (sprite.xspritehit * sin(M_PI_4)) / sin(M_PI - M_PI_4 - (M_PI_2 - sprite.angle));
		else if (sprite.quadrant == 1)
			sprite.dist2add = (sprite.xspritehit * sin(M_PI_4)) / sin(M_PI - M_PI_4 - (sprite.angle - (3 * M_PI / 2)));
		else if (sprite.quadrant == 2)
			sprite.dist2add = (1 - sprite.xspritehit * sin(M_PI_4)) / sin(M_PI - M_PI_4 - ((3 * M_PI / 2) - sprite.angle));
		else if (sprite.quadrant == 3)
			sprite.dist2add = (1 - sprite.xspritehit * sin(M_PI_4)) / sin(M_PI - M_PI_4 - (sprite.angle - M_PI_2));
	}
	else if (sprite.yhit == 1)
	{
		if (sprite.quadrant == 4)
			sprite.dist2add = ((1 - sprite.xspritehit) * sin(M_PI_4)) / sin(M_PI - M_PI_4 - sprite.angle);
		else if (sprite.quadrant == 1)
			sprite.dist2add = (sprite.xspritehit * sin(M_PI_4)) / sin(M_PI - M_PI_4 - ((2 * M_PI) - sprite.angle));
		else if (sprite.quadrant == 2)
			sprite.dist2add = ((1 - sprite.xspritehit) * sin(M_PI_4)) / sin(M_PI - M_PI_4 - (sprite.angle - M_PI));
		else if (sprite.quadrant == 3)
			sprite.dist2add = (sprite.xspritehit * sin(M_PI_4)) / sin(M_PI - M_PI_4 - (M_PI - sprite.angle));
	}
	printf("xspritehit: %f\n", sprite.xspritehit);
	printf("angle: %f\n", sprite.angle);
	printf("d2a: %f\n", sprite.dist2add);
	sprite.dist2add = (- cos(sprite.angle)) * sprite.xspritehit;
	printf("d2a: %f\n\n", sprite.dist2add);
	return (sprite.dist2add);
}

void	calc_distance_nd_stature(t_cub3d *a, t_sprite sprite)
{
	sprite.dist2hit = hypot(a->rayc.xray - a->rayc.xplyr, a->rayc.yray - a->rayc.yplyr);
		sprite.dist2hit = sprite.dist2hit
				* cos(a->rayc.anglray - a->rayc.dirplyr);
	sprite.dist2add = calc_dist2add(sprite);
	sprite.distance = sprite.dist2hit + sprite.dist2add;
//	sprite.distance = sprite.distance * cos(a->rayc.anglray - a->rayc.dirplyr);

	sprite.stature = a->fconf.xrendersize / sprite.distance;
	sprite.init = (round(a->fconf.yrendersize / 2.0 - sprite.stature / 2));
	sprite.end = (round(a->fconf.yrendersize / 2.0 + sprite.stature / 2));

	a->mlibx.sprite[a->mlibx.nbr_sprite] = sprite;
}

static void	init_sprite(t_cub3d *a)
{
	t_sprite	sprite;
	
//	spr_calc_step(a);
	calc_quadrantsprite(a);
	calc_spriteimpact(a);
	calc_lasthit(a);
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];
	sprite.xpos = (int)a->rayc.yray;
	sprite.ypos = (int)a->rayc.xray;
	
	calc_distance_nd_stature(a, sprite);
	sprite = a->mlibx.sprite[a->mlibx.nbr_sprite];//Vaya chorro-cé


	sprite.ystep = 1.0 * a->mlibx.xpmwall[4].height / sprite.stature;
	sprite.yfloat = sprite.ystep * (sprite.init + sprite.stature / 2
		- a->fconf.yrendersize / 2);

	sprite.sequence = a->mlibx.nbr_sprite;
	sprite.first_ray = a->rayc.nbr_ray;
	sprite.first_x = sprite.x;
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
			{
				a->mlibx.sprite[c].last_ray = a->rayc.nbr_ray;
				return ;
			}
		c++;
	}
	init_sprite(a);
	a->mlibx.nbr_sprite++;
}
