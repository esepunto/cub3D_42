/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:54:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/02 10:43:26 by ssacrist         ###   ########.fr       */
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

int			draw(t_cub3d *a)
{
	//Calculamos el delta time:
//	a->steal.delta = millis() - a->steal.lasttime;//Imposible a priori: no puedo usar librería de tiempo
	
	/*
	** *+*+ Pintar con minilbx *+*+*
	*/
	draw_ceilling(a);
	//Pintar el cielo y el suelo:
/*	noStroke();
	fill(30);
	rect(0,0,anchoPantalla, altoPantalla/2); //Cielo
	fill(120);
	rect(0,altoPantalla/2,anchoPantalla, altoPantalla/2); //Suelo
*/
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

			//Si el rayo sale del mapa, o si colisiona con un muro, salimos del bucle while: // ft_strlen(a->fconf.map.maze[a->steal.yray])
			if (a->steal.xray < 0 || a->steal.xray >= a->fconf.map.col
				|| a->steal.yray < a->fconf.map.first_line || a->steal.yray >= a->fconf.map.row
				|| a->fconf.map.maze[(int)a->steal.yray][(int)a->steal.xray] == '1')
			{
				knock = 1;
			}
		}

		//Calcular la distancia corregida del jugador al punto de colisión:
		a->steal.distance = sqrt(pow(a->steal.xray - a->steal.xplyr, 2) + pow(a->steal.yray - a->steal.yplyr, 2) );
		a->steal.distance = a->steal.distance * cos(a->steal.anglray - a->steal.dirplyr);

		//Calcular la altura del muro:
		a->steal.staturewall = fmin(a->fconf.yrendersize, a->fconf.yrendersize / a->steal.distance);
//		printf("punto alto muro: |%d| - punto bajo muro : |%d|\n", a->steal.initwall, a->steal.endwall);
		
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
*/		draw_line(a, a->steal.nbr_ray, a->steal.initwall, a->steal.nbr_ray, a->steal.endwall, 0x00C04225);
/*		line(x, nTecho, x, nSuelo);
	
		//Actualizar la variable lastTime con el tiempo actual
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
		//Avanzar la posición del jugador hacia delante:
		a->steal.xplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		printf("xplayer: |%f| - yplayer: |%f|\n", a->steal.xplyr, a->steal.yplyr);
		
		//Si el jugador ha entrado dentro de una pared se deshace el movimiento:
		if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
		{
			a->steal.xplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			a->steal.yplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			printf("**¡¡MURO!!** xplayer: |%f| - yplayer: |%f|\n", a->steal.xplyr, a->steal.yplyr);
		}
	}

	//Giro a la izquierda:
	else if (a->rayc.keycode == KEY_LOOK_LEFT)
	{
		a->steal.dirplyr -= a->steal.rotspeed * a->steal.delta;
		printf("dirplayer: |%f|\n", a->steal.dirplyr);
	}

	//Giro a la derecha:
	else if (a->rayc.keycode == KEY_LOOK_RIGHT)
	{
		a->steal.dirplyr += a->steal.rotspeed * a->steal.delta;
		printf("dirplayer: |%f|\n", a->steal.dirplyr);
	}

	//Moverse hacia atrás:
	else if (a->rayc.keycode == KEY_MOVE_BACK)
	{
		a->steal.xplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		printf("xplayer: |%f| - yplayer: |%f|\n", a->steal.xplyr, a->steal.yplyr);
		
		if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
		{
			a->steal.xplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			a->steal.yplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
			printf("**¡¡MURO!!** xplayer: |%f| - yplayer: |%f|\n", a->steal.xplyr, a->steal.yplyr);
		}
	}
	draw(a);
	return (0);
}



