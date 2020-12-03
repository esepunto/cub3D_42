/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/03 09:35:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		draw_ceilling(t_cub3d *a)
{
	int	x;
	int	y;
	
	x = 0;
	while(x <= a->fconf.xrendersize)
	{
		y = 0;
		while(y <= a->fconf.yrendersize)
		{
			if (y <= a->fconf.yrendersize / 2)
				mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, x, y, a->fconf.ceilcolor);
			else if (y > a->fconf.yrendersize / 2)
				mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, x, y, a->fconf.floorcolor);
			y++;
		}
		x++;
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

void		calc_quadrant(t_cub3d *a)
{
	double	val;

	val = fmod(a->steal.anglray, 6);
	if ((val >=0 && val < 1.5) || (val >= -6 && val < -4.5))
		a->steal.quadrant = 1;
	if ((val >=1.5 && val < 3) || (val >= -4.5 && val < -3))
		a->steal.quadrant = 2;
	if ((val >=3 && val < 4.5) || (val >= -3 && val < -1.5))
		a->steal.quadrant = 3;
	if ((val >=4.5 && val < 6) || (val >= -1.5 && val < -0))
		a->steal.quadrant = 4;
	printf("Ángulo: |%f| - Cuadrante: |%d|\n", val, a->steal.quadrant);
	
}

/*
** Every ray that hits a wall impact on x,y coordenates.
** To calculate the texture of the wall impacted by the ray,
** we need to know 2 data:
**   1. The exactly x or y coordenate when ray impacts (no decimals coordenate)
**   2. The quadrant of the ray's angle.
** So:
** Impact on x coordenate:
**    Texture N on 1 and 4 quadrants.
**    Texture S on 2 and 3 quadrants.
** Impact on y coordenate:
**    Texture E on 1 and 2 quadrants.
**    Texture W on 3 and 4 quadrants.
*/

void		calc_texture(t_cub3d *a)
{
	calc_quadrant(a);
}

int			draw(t_cub3d *a)
{
	//Calculamos el delta time:
	//	a->steal.delta = millis() - a->steal.lasttime;//Imposible a priori: no puedo usar librería de tiempo
	
	//Pintar el cielo y el suelo:
	draw_ceilling(a);

	//Trazar un rayo desde cada una de las columnas de la pantalla:
	a->steal.nbr_ray = 0;
	while (a->steal.nbr_ray < a->fconf.xrendersize)
	{
		//La posición inicial del rayo será la del jugador:
		a->steal.xray = a->steal.xplyr;
		a->steal.yray = a->steal.yplyr;

		//Calculamos su ángulo inicial:
		a->steal.anglray = (a->steal.dirplyr - FOV / 2.0) + a->steal.nbr_ray * (FOV / a->fconf.xrendersize);
	
		//Calculamos el incremento:
		a->steal.xincrease = cos(a->steal.anglray) * a->steal.modulo;
		a->steal.yincrease = sin(a->steal.anglray) * a->steal.modulo;
	
		//Calcular la trayectoria del rayo, paso a paso:
		int knock = 0;
		while (knock <= 0)
		{
			//Calcular un nuevo punto de la trayectoria:
			a->steal.xray += a->steal.xincrease;
			a->steal.yray += a->steal.yincrease;
			
//			printf("yray: |%f| - xincrease: |%f|\n", a->steal.yray, a->steal.xincrease);
//			printf("xhit: |%d| - yhit: |%d|\n", a->steal.xhit, a->steal.yhit);
			

			//Si el rayo sale del mapa, o si colisiona con un muro, salimos del bucle while: // ft_strlen(a->fconf.map.maze[a->steal.yray])
			if (a->fconf.map.maze[(int)a->steal.yray][(int)a->steal.xray] == '1')
			{
/*				if (fmod(a->steal.xray, a->steal.xincrease) == 0)
				{
					a->steal.xhit = 1;
					printf("xray: |%f| - xincrease: |%f|\n", a->steal.xray, a->steal.xincrease);
					printf("xhit: |%d| - yhit: |%d|\n", a->steal.xhit, a->steal.yhit);
				}
				else
					a->steal.xhit = 0;
				if (fmod(a->steal.yray, a->steal.yincrease) == 0)
				{
					a->steal.yhit = 1;
					printf("yray: |%f| - yincrease: |%f|\n", a->steal.yray, a->steal.yincrease);
					printf("yhit: |%d| - yhit: |%d|\n", a->steal.xhit, a->steal.yhit);
				}
				else
					a->steal.yhit = 0;

*/				knock = 1;
			}
		}
		calc_texture(a);


		//Calcular la distancia corregida del jugador al punto de colisión:
		a->steal.distance = sqrt(pow(a->steal.xray - a->steal.xplyr, 2) + pow(a->steal.yray - a->steal.yplyr, 2) );
		a->steal.distance = a->steal.distance * cos(a->steal.anglray - a->steal.dirplyr);

		//Calcular la altura del muro:
		a->steal.staturewall = fmin(a->fconf.yrendersize, a->fconf.yrendersize / a->steal.distance);
//		a->steal.staturewall = a->fconf.yrendersize / a->steal.distance;
		
		//Calcular el píxel de la pantalla donde hay que empezar a dibujar el muro (initwall) y donde hay que acabar (endwall)
		a->steal.initwall = (int)((float)(a->fconf.yrendersize) / 2.0 - a->steal.staturewall / 2);
		a->steal.endwall = (int)((float)(a->fconf.yrendersize) / 2.0 + a->steal.staturewall / 2);

		/*
		** Antes de dibujar la línea vertical hay que elegir una tonalidad de color,
		** que vendrá dada por la distancia.
		** Para ello se utiliza la función map() de processing:
		*/

		//Calcular una tonalidad para la columna, que dependerá de la distancia (cuanto más lejos, más oscuro)
/*		float tonalidad = map(min(distancia, 7), 0, 7, 255, 40);
		stroke(int(tonalidad));

		//Dibujar la línea vertical:
		printf("punto alto muro: |%d| - punto bajo muro : |%d|\n", a->steal.initwall, a->steal.endwall);
*/	
		double b;
		b = a->steal.initwall;
		while (b++ < a->steal.endwall)
			mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, a->steal.nbr_ray, b, 0x0101010);
	
/*		//Actualizar la variable lastTime con el tiempo actual
		lastTime = millis();
*/		a->steal.nbr_ray++;
	}
	return (0);
}

//Controles del jugador:
int			teclado(int keycode, t_cub3d *a)
{
	a->rayc.keycode = keycode;
//	printf("keycode: |%d|\n", keycode);
	//Moverse hacia delante:
	if (a->rayc.keycode == KEY_ESC)
		closed(a);
	else if (a->rayc.keycode == KEY_MOVE_FRONT)
	{
		a->steal.xplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
		{
			a->steal.xplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			a->steal.yplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		}
	}
	else if (a->rayc.keycode == KEY_MOVE_BACK)
	{
		a->steal.xplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
		{
			a->steal.xplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			a->steal.yplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		}
	}
	else if (a->rayc.keycode == KEY_MOVE_RIGHT)
	{
		a->steal.xplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
		{
			a->steal.xplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			a->steal.yplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		}
	}
	else if (a->rayc.keycode == KEY_MOVE_LEFT)
	{
		a->steal.xplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
		{
			a->steal.xplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			a->steal.yplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		}
	}
	else if (a->rayc.keycode == KEY_LOOK_LEFT)
		a->steal.dirplyr -= a->steal.rotspeed * a->steal.delta;
	else if (a->rayc.keycode == KEY_LOOK_RIGHT)
		a->steal.dirplyr += a->steal.rotspeed * a->steal.delta;
	draw(a);
//	printf("Cuadrante ángulo: |%f|\n", fmod(a->steal.anglray - FOV / 2, 6));
	return (0);
}



