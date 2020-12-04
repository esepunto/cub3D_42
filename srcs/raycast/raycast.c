/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/04 14:30:06 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_texture(t_cub3d *a)
{
	if (a->steal.xhit == 1 && a->steal.yhit == 1)
		return ;
	if (a->steal.xhit == 1)
	{
		if (a->steal.quadrant == 4 || a->steal.quadrant == 1)
			a->steal.wallcolor = 0x40343B;//North
		else if (a->steal.quadrant == 2 || a->steal.quadrant == 3)
			a->steal.wallcolor = 0x40583B;//South
	}
	else if (a->steal.yhit == 1)
	{
		if (a->steal.quadrant == 1 || a->steal.quadrant == 2)
			a->steal.wallcolor = 0x10343B;//East
		else if (a->steal.quadrant == 3 || a->steal.quadrant == 4)
			a->steal.wallcolor = 0x4034aB;//West
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

	val = fmod(a->steal.anglray, M_PI * 2);
	if ((val >= 0 && val < M_PI_2) || (val >= - (M_PI * 2) && val < - M_PI_2 * 3))
		a->steal.quadrant = 1;
	if ((val >= M_PI_2 && val < M_PI) || (val >= - (M_PI_2 * 3) && val < -M_PI))
		a->steal.quadrant = 2;
	if ((val >= M_PI && val < M_PI_2 * 3) || (val >= - M_PI && val < -M_PI_2))
		a->steal.quadrant = 3;
	if ((val >= M_PI_2 * 3 && val < M_PI * 2) || (val >= - M_PI_2 && val < -0))
		a->steal.quadrant = 4;
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
	if ((int)a->steal.xray != (int)(a->steal.xray - a->steal.xincrease))
		a->steal.xhit = 1;
	else
		a->steal.xhit = 0;
	if ((int)a->steal.yray != (int)(a->steal.yray - a->steal.yincrease))
		a->steal.yhit = 1;
	else
		a->steal.yhit = 0;
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
	int hit = 0;
	while (hit == 0)
	{
		a->steal.xray += a->steal.xincrease;
		a->steal.yray += a->steal.yincrease;
		if (a->fconf.map.maze[(int)a->steal.yray][(int)a->steal.xray] == '1')
		{
			calc_wallimpact(a);
			calc_quadrant(a);
			calc_texture(a);
			hit = 1;
		}
	}
}

/*
**  +*+*+*+* The raycast algorithm *+*+*+*+*
**
** 1. Trazar un rayo desde cada una de las columnas de la pantalla
** 2. La posición inicial del rayo será la del jugador.
** 3. Calculamos su ángulo inicial.
** 4. Calculamos el incremento.
** 5. Calcular el impacto.
** 6. Calcular la distancia corregida del jugador al punto de colisión.
** 7. Calcular la altura del muro.
** 8. Calcular el píxel de la pantalla donde hay que empezar a dibujar el muro
**    (initwall) y donde hay que acabar (endwall).
*/

int		throw_rays(t_cub3d *a)
{
	draw_background(a);
	a->steal.nbr_ray = 0;
	while (a->steal.nbr_ray < a->fconf.xrendersize)
	{
		a->steal.xray = a->steal.xplyr;
		a->steal.yray = a->steal.yplyr;
		a->steal.anglray = (a->steal.dirplyr - FOV / 2.0) + a->steal.nbr_ray * (FOV / a->fconf.xrendersize);
		a->steal.xincrease = cos(a->steal.anglray) * a->steal.modulo;
		a->steal.yincrease = sin(a->steal.anglray) * a->steal.modulo;
		ifimpact(a);
		a->steal.distance = sqrt(pow(a->steal.xray - a->steal.xplyr, 2) + pow(a->steal.yray - a->steal.yplyr, 2) );
		a->steal.distance = a->steal.distance * cos(a->steal.anglray - a->steal.dirplyr);
		a->steal.staturewall = fmin(a->fconf.yrendersize, a->fconf.yrendersize / a->steal.distance);
		a->steal.initwall = (int)((float)(a->fconf.yrendersize) / 2.0 - a->steal.staturewall / 2);
		a->steal.endwall = (int)((float)(a->fconf.yrendersize) / 2.0 + a->steal.staturewall / 2);
		brush_wall(a);
		a->steal.nbr_ray++;
	}
	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
	return (0);
}
