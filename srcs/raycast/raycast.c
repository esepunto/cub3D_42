/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/07 14:40:36 by ssacrist         ###   ########.fr       */
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
	printf("\nalt: |%f| - init: |%d| - end: |%d|\n", a->rayc.staturewall, a->rayc.initwall, a->rayc.endwall);
	printf("xdist: |%f| - ydist: |%f|\n", a->rayc.xdistance, a->rayc.ydistance);
	printf("dist: |%f|\n", a->rayc.distance);
	printf("xhit: |%d| - yhit: |%d|\n", a->rayc.xhit, a->rayc.yhit);
	printf("ang: |%f| - resto: |%f| - quad: |%d|\n\n", a->rayc.anglray, val, a->rayc.quadrant);
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

void	ifimpact_x(t_cub3d *a)
{
	int	xray;
	int	yray;

	a->rayc.yhit = 0;
	xray = a->rayc.xray;
	yray = a->rayc.yray;
	while ((int)yray >= a->fconf.map.first_line && (int)yray <= a->fconf.map.row
			&& (int)xray >= 0 && (int)xray <= (int)a->fconf.map.col)
	{
		if (a->fconf.map.maze[(int)yray][(int)xray] == '1')
		{
			a->rayc.xdistance = hypot(xray - a->rayc.xplyr, yray - a->rayc.yplyr);
			printf("xdist: |%f|\n", a->rayc.xdistance);
			a->rayc.xray = xray;
			a->rayc.yray = yray;
			a->rayc.xhit = 1;
			return ;
		}
		xray += a->rayc.xincrease;
		yray += xray * tan(a->rayc.anglray);
	}
}

void	ifimpact_y(t_cub3d *a, int xray, int yray)
{
	a->rayc.yhit = 0;
	while ((int)yray >= a->fconf.map.first_line && (int)yray <= a->fconf.map.row
			&& (int)xray >= 0 && (int)xray <= (int)a->fconf.map.col)
	{
		if (a->fconf.map.maze[(int)yray][(int)xray] == '1')
		{
			a->rayc.ydistance = hypot(xray - a->rayc.xplyr, yray - a->rayc.yplyr);
			printf("ydist: |%f|\n", a->rayc.ydistance);
			if (a->rayc.ydistance < a->rayc.xdistance)
			{
				a->rayc.xray = xray;
				a->rayc.yray = yray;
			}
			a->rayc.yhit = 1;
			return ;
		}
		yray += a->rayc.yincrease;
		xray += yray / tan(a->rayc.anglray);
	}
}

void	ifimpact(t_cub3d *a)
{
	double	xray;
	double	yray;
	
	xray = a->rayc.xray;
	yray = a->rayc.yray;
	ifimpact_x(a);
	ifimpact_y(a, xray, yray);
	if (a->rayc.xdistance < a->rayc.ydistance && a->rayc.xhit == 1)
	{
		a->rayc.yhit = 0;
		a->rayc.distance = a->rayc.xdistance;
	}
	else if (a->rayc.ydistance < a->rayc.xdistance && a->rayc.yhit == 1)
	{
		a->rayc.xhit = 0;
		a->rayc.distance = a->rayc.ydistance;
	}
	calc_quadrant(a);
	calc_texture(a);
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
	a->fconf.sizecell = a->fconf.yrendersize / a->fconf.map.nbrlines;
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

		if (a->rayc.xfactor > 0)
			a->rayc.xray = ceil(a->rayc.xray);
		else
			a->rayc.xray = floor(a->rayc.xray);
		if (a->rayc.yfactor > 0)
			a->rayc.yray = ceil(a->rayc.yray);
		else
			a->rayc.yray = floor(a->rayc.yray);


		a->rayc.xincrease = a->rayc.xfactor;
		a->rayc.yincrease = a->rayc.yfactor;

		ifimpact(a);


		//Distancia = cos(angle)/xray - x pos)

		a->rayc.distance = sqrt(pow(a->rayc.xray - a->rayc.xplyr, 2)
				+ pow(a->rayc.yray - a->rayc.yplyr, 2));
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
