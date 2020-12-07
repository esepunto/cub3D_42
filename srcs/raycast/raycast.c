/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/07 09:53:54 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_texture(t_cub3d *a)
{
	if (a->rayc.xhit == 1 && a->rayc.yhit == 1)
		return ;
	if (a->rayc.xhit == 1)
	{
		if (a->rayc.quadrant == 4 || a->rayc.quadrant == 1)
			a->rayc.wallcolor = 0x40343B;
		else if (a->rayc.quadrant == 2 || a->rayc.quadrant == 3)
			a->rayc.wallcolor = 0x40583B;
	}
	else if (a->rayc.yhit == 1)
	{
		if (a->rayc.quadrant == 1 || a->rayc.quadrant == 2)
			a->rayc.wallcolor = 0x10343B;
		else if (a->rayc.quadrant == 3 || a->rayc.quadrant == 4)
			a->rayc.wallcolor = 0x4034aB;
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

/*
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
			hit = 1;
		}
	}
}
*/

void	ifimpact(t_cub3d *a)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (a->fconf.map.maze[(int)a->rayc.yray][(int)a->rayc.xray] == '1')
		{
//			printf("x: %f - y: %f\n", a->rayc.xincrease, a->rayc.yincrease);
			calc_wallimpact(a);
			calc_quadrant(a);
			calc_texture(a);
			hit = 1;
		}
		a->rayc.xray++;
		a->rayc.yray++;
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

		if (isgreaterequal(cos(a->rayc.anglray), 0.0))
			a->rayc.xfactor = ceil(cos(a->rayc.anglray));
		else
			a->rayc.xfactor = floor(cos(a->rayc.anglray));
		if (isgreaterequal(sin(a->rayc.anglray), 0.0))		
			a->rayc.yfactor = ceil(sin(a->rayc.anglray));
		else
			a->rayc.yfactor = floor(sin(a->rayc.anglray));

		
//		printf("sin: |%f|\n\n",tan(a->rayc.anglray));
//		printf("PRE xray: |%f| - yray: |%f|\n", a->rayc.xray, a->rayc.yray);
		a->rayc.xray += (int)(a->rayc.xray + 1.0) - a->rayc.xray;
		a->rayc.yray += (int)(a->rayc.yray + 1.0) - a->rayc.yray;
//		printf("POS xray: |%f| - yray: |%f|\n", a->rayc.xray, a->rayc.yray);
		printf("incremento xray: |%f|\n", a->rayc.xray - a->rayc.xplyr);
		printf("incremento yray: |%f|\n\n", a->rayc.yray - a->rayc.yplyr);



//a->minimap.sizecell = a->fconf.yrendersize / a->fconf.map.nbrlines;
		
		ifimpact(a);

		//Distania = cos(angle)/xray - x pos)
		a->rayc.distance = cos(a->rayc.anglray) / (a->rayc.xray - a->rayc.xplyr) / 2;
//		a->rayc.distance = sqrt(pow(a->rayc.xray - a->rayc.xplyr, 2)
//				+ pow(a->rayc.yray - a->rayc.yplyr, 2));
		a->rayc.distance = a->rayc.distance
				* cos(a->rayc.anglray - a->rayc.dirplyr);
		a->rayc.staturewall = fmin(a->fconf.yrendersize,
				a->fconf.yrendersize / a->rayc.distance);
		a->rayc.initwall = (int)((float)(a->fconf.yrendersize) / 2.0
				- a->rayc.staturewall / 2);
		a->rayc.endwall = (int)((float)(a->fconf.yrendersize) / 2.0
				+ a->rayc.staturewall / 2);
		pointillism(a);
		a->rayc.nbr_ray++;
	}
	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
	return (0);
}
/*
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
		a->rayc.distance = sqrt(pow(a->rayc.xray - a->rayc.xplyr, 2)
				+ pow(a->rayc.yray - a->rayc.yplyr, 2));
//		hypot(x, y) returns sqrt(x*x + y*y)
		a->rayc.distance = a->rayc.distance
				* cos(a->rayc.anglray - a->rayc.dirplyr);
		a->rayc.staturewall = fmin(a->fconf.yrendersize,
				a->fconf.yrendersize / a->rayc.distance);
		a->rayc.initwall = (int)((float)(a->fconf.yrendersize) / 2.0
				- a->rayc.staturewall / 2);
		a->rayc.endwall = (int)((float)(a->fconf.yrendersize) / 2.0
				+ a->rayc.staturewall / 2);
		pointillism(a);
		a->rayc.nbr_ray++;
	}
	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
	return (0);
}*/
