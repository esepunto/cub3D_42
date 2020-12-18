/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/18 10:25:40 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Every ray that hits a wall impact on x,y coordenates.
** To calculate the texture of the wall impacted by the ray, we
** need to know 2 data:
**   1. The exactly x or y coordenate when ray impacts.
**   2. The quadrant of the ray's angle.
** So:
** If impact on x coordenate:
**    Texture N on 1 and 4 quadrants.
**    Texture S on 2 and 3 quadrants.
** If impact on y coordenate:
**    Texture E on 1 and 2 quadrants.
**    Texture W on 3 and 4 quadrants.
*/

void	calc_texture(t_cub3d *a)
{
	if (a->rayc.xhit == 1 && a->rayc.yhit == 1)
		return ;
	if (a->rayc.xhit == 1)
	{
		if (a->rayc.quadrant == 4 || a->rayc.quadrant == 1)
			a->rayc.wall = 0;//North
		else if (a->rayc.quadrant == 2 || a->rayc.quadrant == 3)
			a->rayc.wall = 1;//South
	}
	else if (a->rayc.yhit == 1)
	{
		if (a->rayc.quadrant == 1 || a->rayc.quadrant == 2)
			a->rayc.wall = 2;//East
		else if (a->rayc.quadrant == 3 || a->rayc.quadrant == 4)
			a->rayc.wall = 3;//West
	}
}

/*
** Asign to every ray that hits a wall
** its quadrant's angle (1, 2, 3 or 4).
**
**       |
**   4   |   1
** ______|_______
**       |
**   3   |   2
**       |
*/

void	calc_quadrant(t_cub3d *a)
{
	double	val;

	val = fmod(a->rayc.anglray, M_PI * 2);
	if ((val >= 0 && val < M_PI_2) || (val >= -(M_PI * 2) && val < -M_PI_2 * 3))
		a->rayc.quadrant = 1;
	if ((val >= M_PI_2 && val < M_PI) || (val >= -(M_PI_2 * 3) && val < -M_PI))
		a->rayc.quadrant = 2;
	if ((val >= M_PI && val < M_PI_2 * 3) || (val >= -M_PI && val < -M_PI_2))
		a->rayc.quadrant = 3;
	if ((val >= M_PI_2 * 3 && val < M_PI * 2) || (val >= -M_PI_2 && val < -0))
		a->rayc.quadrant = 4;
}

/*
** To calc where coodinate (x or y) the impact is.
** xhit = 1, if immpact on x coordenate.
** yhit = 1, if immpact on y coordenate.
** Of course, every colision point have 2 ccordenates. When I say
** that impact on x coordenate, what I mean is that the x coordenate
** of the ray is changed of cell in the last advance.
*/

void	calc_wallimpact(t_cub3d *a)
{
	if ((int)a->rayc.xray != (int)(a->rayc.xray - a->rayc.xincrease))
		a->rayc.xhit = 1;
	else
		a->rayc.xhit = 0;
	if ((int)a->rayc.yray != (int)(a->rayc.yray - a->rayc.yincrease))
		a->rayc.yhit = 1;
	else
		a->rayc.yhit = 0;
}

void	calc_step(t_cub3d *a)
{
	if (cos(a->rayc.anglray) >= 0.0)
		a->rayc.xstep = ceil(cos(a->rayc.anglray));
	else
		a->rayc.xstep = floor(cos(a->rayc.anglray));
	if (sin(a->rayc.anglray) >= 0.0)		
		a->rayc.ystep = ceil(sin(a->rayc.anglray));
	else
		a->rayc.ystep = floor(sin(a->rayc.anglray));
}


void	if_impact(t_cub3d *a)
{
	a->rayc.hit = 0;
	while (a->rayc.hit == 0 && ((int)a->rayc.yray >= a->fconf.map.first_line
			&& (int)a->rayc.yray <= a->fconf.map.row
			&& a->rayc.xray >= 0 && (size_t)a->rayc.xray <= a->fconf.map.col))
	{
		if (a->rayc.xhypo2coord < a->rayc.yhypo2coord)
		{
			a->rayc.xhypo2coord += a->rayc.xhypo;
			a->rayc.xray += a->rayc.xstep;
			a->rayc.xhit = 1;
			a->rayc.yhit = 0;
		}
		else
		{
			a->rayc.yhypo2coord += a->rayc.yhypo;
			a->rayc.yray += a->rayc.ystep;
			a->rayc.yhit = 1;
			a->rayc.xhit = 0;
		}
		if (a->fconf.map.maze[(int)a->rayc.yray][(int)a->rayc.xray] == '1')
			a->rayc.hit = 1;
	}
	if (a->rayc.xhit == 1 && a->rayc.hit == 1)
		a->rayc.distance = a->rayc.xhypo2coord;// - a->rayc.xhypo;//Tengo mis dudas de si restarle xhypo
	else if (a->rayc.yhit == 1 && a->rayc.hit == 1)
		a->rayc.distance = a->rayc.yhypo2coord;// - a->rayc.yhypo;//Tengo mis dudas de si restarle yhypo
}

void	calc_hypotenuses(t_cub3d *a)
{
	if (a->rayc.xstep == 1)
		a->rayc.xdist2coord = ceil(a->rayc.xray) - a->rayc.xray;
	else if (a->rayc.xstep == -1)
		a->rayc.xdist2coord = floor(a->rayc.xray) - a->rayc.xray;
	if (a->rayc.ystep == 1)
		a->rayc.ydist2coord = ceil(a->rayc.yray) - a->rayc.yray;
	else if (a->rayc.ystep == -1)
		a->rayc.ydist2coord = floor(a->rayc.yray) - a->rayc.yray;
	a->rayc.xhypo2coord = a->rayc.xdist2coord / cos(a->rayc.anglray);
	a->rayc.yhypo2coord = a->rayc.ydist2coord / sin(a->rayc.anglray);
	a->rayc.xhypo = a->rayc.xstep / cos(a->rayc.anglray);
	a->rayc.yhypo = a->rayc.ystep / sin(a->rayc.anglray);//Ojo, review
}

/*
** Every ray that hits a wall impact on x,y coordenates.
** To calculate the texture of the wall impacted by the ray, we
** need to know 2 data:
**   1. The exactly x or y coordenate when ray impacts.
**   2. The quadrant of the ray's angle.
** So:
** If impact on x coordenate:
**    Texture N on 1 and 4 quadrants.
**    Texture S on 2 and 3 quadrants.
** If impact on y coordenate:
**    Texture E on 1 and 2 quadrants.
**    Texture W on 3 and 4 quadrants.
*/

void	ifimpact(t_cub3d *a)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		a->rayc.xray += a->rayc.xincrease;
		a->rayc.yray += a->rayc.yincrease;
		if (a->fconf.map.maze[(int)a->rayc.yray][(int)a->rayc.xray] == '1')
		{
//			printf("x: %f - y: %f\n", a->rayc.xincrease, a->rayc.yincrease);
			calc_wallimpact(a);
			calc_quadrant(a);
			calc_texture(a);
			calc_step(a);
			hit = 1;
		}
	}
}


/*
**  +*+*+*+* The raycast algorithm *+*+*+*+*
**
** 1. Throw a ray from each of the columns on the screen.
** 2. The ray's init position is the player's position (lines 135-136).
** 3. Calculate its initial angle (line 137).
** 4. Calc the increment (lines 138-139).
** 5. Calc the impact (line 140).
** 6. Calc the corrected player's distance to the hit point (lines 141-142).
** 7. Calc the height of the wall (line 143).
** 8. Calc the screen pixel where we should start drawing the wall
**    (initwall) and where to end up (endwall) (lines 144-145).
** 9. Save on an image the picture to paint (line 146).
*/

int		throw_rays(t_cub3d *a)
{
	a->rayc.nbr_ray = 0;
	while (a->rayc.nbr_ray < a->fconf.xrendersize)
	{
		a->rayc.xray = a->rayc.xplyr;
		a->rayc.yray = a->rayc.yplyr;
		a->rayc.anglray = (a->rayc.dirplyr - a->rayc.fov / 2.0)
				+ a->rayc.nbr_ray * (a->rayc.fov / a->fconf.xrendersize);
		a->rayc.xincrease = cos(a->rayc.anglray) * a->rayc.modulo;
		a->rayc.yincrease = sin(a->rayc.anglray) * a->rayc.modulo;
		ifimpact(a);
		a->rayc.distance = hypot(a->rayc.xray - a->rayc.xplyr, a->rayc.yray - a->rayc.yplyr);
		a->rayc.distance = a->rayc.distance
				* cos(a->rayc.anglray - a->rayc.dirplyr);
		a->rayc.staturewall = fmin(a->fconf.yrendersize,
				a->fconf.yrendersize / a->rayc.distance);
		a->rayc.initwall = (round((a->fconf.yrendersize) / 2.0 - a->rayc.staturewall / 2));
		a->rayc.endwall = (round((a->fconf.yrendersize) / 2.0 + a->rayc.staturewall / 2));
		calc_texturing(a);
		pointillism(a);
		a->rayc.nbr_ray++;
	}
	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
	return (0);
}
