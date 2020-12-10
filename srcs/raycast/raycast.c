/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/10 12:28:30 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_texture(t_cub3d *a)
{
//	if (a->rayc.xhit == 1 && a->rayc.yhit == 1)
//w		return ;
	if (a->rayc.xhit == 1)
	{
		if (a->rayc.quadrant == 1 || a->rayc.quadrant == 2)
			a->rayc.wallcolor = 0x40343B;
		else if (a->rayc.quadrant == 3 || a->rayc.quadrant == 4)
			a->rayc.wallcolor = 0x40583B;
	}
	else if (a->rayc.yhit == 1)
	{
		if (a->rayc.quadrant == 2 || a->rayc.quadrant == 3)
			a->rayc.wallcolor = 0x10343B;
		else if (a->rayc.quadrant == 4 || a->rayc.quadrant == 1)
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
		a->rayc.quadrant = 2;
	if ((val >= M_PI_2 && val < M_PI) || (val >= -(M_PI_2 * 3) && val < -M_PI))
		a->rayc.quadrant = 3;
	if ((val >= M_PI && val < M_PI_2 * 3) || (val >= -M_PI && val < -M_PI_2))
		a->rayc.quadrant = 4;
	if ((val >= M_PI_2 * 3 && val < M_PI * 2) || (val >= -M_PI_2 && val < -0))
		a->rayc.quadrant = 1;
}


/*
** To calc where coodinate (x or y) the impact is.
** xhit = 1, if immpact on x coordenate.
** yhit = 1, if immpact on y coordenate.
** Of course, every colision point have 2 ccordenates. When I say
** that impact on x coordenate, what I mean is that the x coordenate
** of the ray is changed of cell in the last advance.
*/
/*
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
*/




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


void	calc_distance_x(t_cub3d *a, int xray)
{
	if (a->rayc.quadrant == 1)
		a->rayc.xdistance = (xray - a->rayc.xplyr) / cos(a->rayc.anglray);
	else if (a->rayc.quadrant == 2)
		a->rayc.xdistance = (xray - a->rayc.xplyr) / cos(a->rayc.anglray);
	else if (a->rayc.quadrant == 3)
		a->rayc.xdistance = (xray - a->rayc.xplyr) / cos(a->rayc.anglray);
	else if (a->rayc.quadrant == 4)
		a->rayc.xdistance = (xray - a->rayc.xplyr) / cos(a->rayc.anglray);
}

void	calc_distance_y(t_cub3d *a, int yray)
{
	if (a->rayc.quadrant == 1)
		a->rayc.ydistance = (yray - a->rayc.yplyr) / sin(a->rayc.anglray);
	else if (a->rayc.quadrant == 2)
		a->rayc.ydistance = (yray - a->rayc.yplyr) / sin(a->rayc.anglray);
	else if (a->rayc.quadrant == 3)
		a->rayc.ydistance = (yray - a->rayc.yplyr) / sin(a->rayc.anglray);
	else if (a->rayc.quadrant == 4)
		a->rayc.ydistance = (yray - a->rayc.yplyr) / sin(a->rayc.anglray);


}

void	ifimpact_x(t_cub3d *a, double xray, double yray)
{
	while ((int)yray >= a->fconf.map.first_line && (int)yray <= a->fconf.map.row
			&& xray >= 0 && (size_t)xray <= a->fconf.map.col)
	{
		if (a->fconf.map.maze[(int)yray][(int)xray] == '1')
		{
			calc_distance_x(a, xray);
			a->rayc.xhit = 1;
			a->rayc.distance = a->rayc.xdistance;
			return ;
		}
		xray += a->rayc.xincrease ;
		yray += (a->rayc.xincrease * tan(a->rayc.anglray));
	}
}

void	ifimpact_y(t_cub3d *a, double xray, double yray)
{
	while ((int)yray >= a->fconf.map.first_line && (int)yray <= a->fconf.map.row
			&& xray >= 0 && (size_t)xray <= a->fconf.map.col)
	{
		if (a->fconf.map.maze[(int)yray][(int)xray] == '1')
		{
			calc_distance_y(a, yray);
			if (a->rayc.ydistance != 0 && (a->rayc.ydistance < a->rayc.xdistance || a->rayc.xhit == 0))
			{
				a->rayc.yhit = 1;
				a->rayc.xhit = 0;
				a->rayc.distance = a->rayc.ydistance;
			}
			return ;
		}
		yray += a->rayc.yincrease;
		xray += (a->rayc.yincrease / tan(a->rayc.anglray));
	}
}

void	ifimpact(t_cub3d *a)
{
	double	xray;
	double	yray;
	
	a->rayc.yhit = 0;
	a->rayc.xhit = 0;
	a->rayc.xdistance = 0;
	a->rayc.ydistance = 0;
	a->rayc.distance = 0;
	xray = a->rayc.xray;
	yray = a->rayc.yray;
	ifimpact_x(a, xray, yray);
	ifimpact_y(a, xray, yray);
	print_maze(a);
	calc_texture(a);
}

void	calc_factor(t_cub3d *a)
{
	if (cos(a->rayc.anglray) >= 0.0)
		a->rayc.xfactor = ceil(cos(a->rayc.anglray));
	else
		a->rayc.xfactor = floor(cos(a->rayc.anglray));
	if (sin(a->rayc.anglray) >= 0.0)		
		a->rayc.yfactor = ceil(sin(a->rayc.anglray));
	else
		a->rayc.yfactor = floor(sin(a->rayc.anglray));
}

int		throw_rays(t_cub3d *a)
{
	a->fconf.sizecell = a->fconf.yrendersize / a->fconf.map.nbrlines;
	a->rayc.nbr_ray = 0;
	while (a->rayc.nbr_ray < a->fconf.xrendersize)
	{
		calc_quadrant(a);
			
		a->rayc.xray = a->rayc.xplyr;
		a->rayc.yray = a->rayc.yplyr;
		a->rayc.anglray = (a->rayc.dirplyr - a->rayc.fov / 2.0)
				+ a->rayc.nbr_ray * (a->rayc.fov / a->fconf.xrendersize);

		calc_factor(a);

		a->rayc.xincrease = a->rayc.xfactor;
		a->rayc.yincrease = a->rayc.yfactor;

		ifimpact(a);

		//Distancia = cos(angle)/xray - x pos)
		a->rayc.distance = a->rayc.distance
				* cos(a->rayc.anglray - a->rayc.dirplyr);
		a->rayc.staturewall = fmin(a->fconf.yrendersize,
				a->fconf.yrendersize / a->rayc.distance);
//		a->rayc.staturewall = a->fconf.yrendersize / a->rayc.distance;
		a->rayc.initwall = (round((a->fconf.yrendersize) / 2.0 - a->rayc.staturewall / 2));
		a->rayc.endwall = (round((a->fconf.yrendersize) / 2.0 + a->rayc.staturewall / 2));
//		print_maze(a);
		pointillism(a);
		a->rayc.nbr_ray++;
	}
	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
	return (0);
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
