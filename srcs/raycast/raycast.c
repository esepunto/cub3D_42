/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/07 17:19:06 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** To calc where coodinate (x or y) the impact is.
** xhit = 1, if immpact on x coordenate.
** yhit = 1, if immpact on y coordenate.
** Of course, every colision point have 2 ccordenates. When I say
** that impact on x coordenate, what I mean is that the x coordenate
** of the ray is changed of cell in the last advance.
*/

static void	calc_wallimpact(t_cub3d *a)
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
** Vars xstep and ystep of the ray could only be 1 or -1,
** and indicates the direction of x and y on the
** coordinate axis.
**
** The xstep and ystep are used too to calculate the
** quadrant of the ray (see picture).
**       |
**   3   |   4
** ______|_______
**       |
**   2   |   1
**       |
*/

static void	calc_step_and_quadrant(t_cub3d *a)
{
	if (cos(a->rayc.anglray) >= 0.0)
		a->rayc.xstep = ceil(cos(a->rayc.anglray));
	else
		a->rayc.xstep = floor(cos(a->rayc.anglray));
	if (sin(a->rayc.anglray) >= 0.0)
		a->rayc.ystep = ceil(sin(a->rayc.anglray));
	else
		a->rayc.ystep = floor(sin(a->rayc.anglray));
	if (a->rayc.xstep == 1 && a->rayc.ystep == 1)
		a->rayc.quadrant = 1;
	if (a->rayc.xstep == 1 && a->rayc.ystep == -1)
		a->rayc.quadrant = 4;
	if (a->rayc.xstep == -1 && a->rayc.ystep == 1)
		a->rayc.quadrant = 2;
	if (a->rayc.xstep == -1 && a->rayc.ystep == -1)
		a->rayc.quadrant = 3;
}

/*
**  _______________________________
**  |  char *id | c |   element   |
**  |___________|___|_____________|
**  |	"NO"    | 0 |    north    |
**  |	"SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**  |	"EA"    | 3 |    east     |
**  |___________|___|_____________|
**
** Every ray that hits a wall impact on x,y coordenates.
** To calculate the texture of the wall impacted by the ray, we
** need to know 2 data:
**   1. The exactly x or y coordenate when ray impacts.
**   2. The quadrant of the ray's angle.
** So:
** If impact on x coordenate:
**    Texture W on 1 and 4 quadrants.
**    Texture E on 2 and 3 quadrants.
** If impact on y coordenate:
**    Texture N on 1 and 2 quadrants.
**    Texture S on 3 and 4 quadrants.
*/

static void	choose_texture(t_cub3d *a)
{
	if (a->rayc.xhit == 1 && a->rayc.yhit == 1)
		return ;
	if (a->rayc.xhit == 1)
	{
		if (a->rayc.quadrant == 4 || a->rayc.quadrant == 1)
			a->rayc.wall = 2;
		else if (a->rayc.quadrant == 2 || a->rayc.quadrant == 3)
			a->rayc.wall = 3;
	}
	else if (a->rayc.yhit == 1)
	{
		if (a->rayc.quadrant == 1 || a->rayc.quadrant == 2)
			a->rayc.wall = 0;
		else if (a->rayc.quadrant == 3 || a->rayc.quadrant == 4)
			a->rayc.wall = 1;
	}
}

static void	ifimpact(t_cub3d *a)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		a->rayc.xray += a->rayc.xincrease;
		a->rayc.yray += a->rayc.yincrease;
		if (a->fconf.map.maze[(int)a->rayc.yray][(int)a->rayc.xray] == '2')
			found_sprite(a);
//		printf("raycast\n");
		if (a->fconf.map.maze[(int)a->rayc.yray][(int)a->rayc.xray] == '1')
		{
			calc_wallimpact(a);
			calc_step_and_quadrant(a);
			choose_texture(a);
			hit = 1;
		}
	}
}

/*
**  +*+*+*+* The raycast algorithm *+*+*+*+*
**
** 1. Throw a ray from each of the columns on the screen.
** 2. The ray's init position is the player's position (lines 168-169).
** 3. Calculate its initial angle (line 180).
** 4. Calc the increment (lines 172-173).
** 5. Calc the impact on wall (line 174).
** 6. Calc the corrected player's distance to the hit point (lines 175-178).
** 7. Calc the height of the wall (line 179).
** 8. Calc the screen pixel where we should start drawing the wall
**    (initwall) and where to end up (endwall) (lines 180-183).
** 9. Save on an image the picture to paint (lines 184-185).
**
**
** To avoid distorted images (it depends by resolution on config file):
** a->rayc.staturewall =
**  a->fconf.yrendersize / a->rayc.distance *
**  a->fconf.xrendersize / a->fconf.yrendersize; >Multiply by resolution factor
** And this is the same that:
** a->rayc.staturewall = a->fconf.xrendersize / a->rayc.distance;
**
** Var a->rayc.aux is used to paint wall when player is
** so close to the wall and stature's wall is more height
** than windows' height.
*/

void		throw_rays(t_cub3d *a)
{
	a->rayc.nbr_ray = 0;
	clean_sprites(a);
//	if (a->rayc.buffer)
//		free(a->rayc.buffer);
//	if (!(a->rayc.buffer = (t_dist *)malloc(a->fconf.xrendersize * sizeof(t_dist))))
//		msg_err("No memory for buffer!");
	while (a->rayc.nbr_ray < a->fconf.xrendersize)
	{
		a->rayc.aux = 0;
		a->mlibx.sprite->aux = 0;
		a->rayc.xray = a->rayc.xplyr;
		a->rayc.yray = a->rayc.yplyr;
		a->rayc.anglray = (a->rayc.dirplyr - a->rayc.fov / 2.0)
				+ a->rayc.nbr_ray * (a->rayc.fov / a->fconf.xrendersize);
		a->rayc.xincrease = cos(a->rayc.anglray) * a->rayc.modulo;
		a->rayc.yincrease = sin(a->rayc.anglray) * a->rayc.modulo;
		ifimpact(a);
		a->rayc.distance = hypot(a->rayc.xray - a->rayc.xplyr,
								a->rayc.yray - a->rayc.yplyr);
		a->rayc.distance = a->rayc.distance
				* cos(a->rayc.anglray - a->rayc.dirplyr);
//		a->rayc.buffer[a->rayc.nbr_ray].dist = a->rayc.distance;
//		printf("buffer_dist[%d]: %f\n", a->rayc.nbr_ray, a->rayc.buffer[a->rayc.nbr_ray].dist);
		a->rayc.staturewall = a->fconf.xrendersize / a->rayc.distance;
		a->rayc.initwall = (round(a->fconf.yrendersize / 2.0
				- a->rayc.staturewall / 2));
		a->rayc.endwall = (round(a->fconf.yrendersize / 2.0
				+ a->rayc.staturewall / 2));
		calc_texturing(a);
		pointillism(a);
//		print_sprites(a);
		a->rayc.nbr_ray++;
	}
	print_sprites(a);
	if (a->mlibx.nbr_sprite)
		paintsprites(a);

	mlx_put_image_to_window(a->mlibx.mlx, a->mlibx.win, a->mlibx.img.img, 0, 0);
}
