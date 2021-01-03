/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:22:58 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/03 18:11:34 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
PSEUDOCÓDIGO

Se pintarán los sprites después de haber pintado todos los rayos de la
	ventana.
Para ello, se tebdrán que almanecer varios datos durante el raycast.
Hallar la parte visible del sprite que hay que pintar (no oculta por muros).
Calcular con el ángulo del jugador cómo debo pintar el sprite.
	1. Si una coordenada de la posición del jugador coincide con la del
		sprite, el jugador solo verá una cara.
	2. En caso contrario, el jugador verá desde su posición dos caras del
		sprite, y hay que hallar qué porcentaje de visión corresponde a cada
		una. Esto depende del ángulo del jugador. Si es 45º (M_PI_4) o múltiplo,
		el 50% de lo que se pinta correspoonde a una cara y el 50 % restante a
		la otra. Un algoritmo calcula estos porcentajes a partir del ángulo.
	3. Este algoritmo depende de:
		a. Ángulo del jugador.
		b. xhit en ambas caras (para conocer la parte visible)
		c. Quadrante en que se encuentra el sprite.
	4. Para pintar se necesita:
		a. Los rayos del raycast inicial y final del sprite (en qué píxel del eje X
			empezamos a pintar el sprite y en cuál acabamos).
		b. stature del sprite (conocido ya por la distancia).
		c. Algoritmo del punto 3.

ALGORITMO.

Basamos el algoritmo en este cuadrante (el mismo ya empleado). Se refiere al
	ángulo del sprite respecto al jugador.
      |
  3   |   4
______|_______
      |
  2   |   1
      |
Cada cuadrante requiere un cálculo diferente. 

QUADRANTE 4.
El punto medio se da en 45º (M_PI_4). 
Como hacemos raycast de izquierda a derecha, primero se ve la cara en la
	impacta el eje de las X y después la cara cuando los rayos impactan en Y.

	1.Impacto en X.
		a. Este punto de impacto se guarda en la variable a->mlibx.sprite[c].x,
			y el del primer rayo se guarda en una variable específica.
		b. Cuanto menor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad = 100 % de la cara X.
			Si es 0.99 >>> visibilidad =   0 % de la cara X. 

	2. Impacto en Y.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del último rayo hay que guardarlo en una variable específica.
		b. Cuanto mayor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad =   0 % de la cara Y.
			Si es 0.99 >>> visibilidad = 100 % de la cara Y. 

	3. Ahora hay que calcular el factor de impresión de cada cara.
		a. Si el ángulo del jugador es M_PI_4 (45º), cada cara tendrá un 50 %.
		b. Algotitmo factor visibilización.
			Si M_PI_2 (90º)
				Multiplicar la visibilidad de cara X por 1 y cara Y por 0.
			Si M_2_PI (0º - 360º)
				Multiplicar la visibilidad de cara X por 0 y cara Y por 1.
			Codificar algoritmo que lo calcule.

QUADRANTE 1.
El punto medio se da en 315º (7PI / 4).

	1. Impacto en Y.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del primer rayo hay que guardarlo en una variable específica.
		b. Cuanto menor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad = 100 % de la cara Y.
			Si es 0.99 >>> visibilidad =   0 % de la cara Y. 

	2. Impacto en X.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del último rayo hay que guardarlo en una variable específica.
		b. Cuanto mayor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad =   0 % de la cara X.
			Si es 0.99 >>> visibilidad = 100 % de la cara X. 

	3. Ahora hay que calcular el factor de impresión de cada cara.
		a. Si el ángulo del jugador es 7PI/4 (315º), cada cara tendrá un 50 %.
		b. Algotitmo factor visibilización.
			Si M_2_PI (0º - 360º)
				Multiplicar la visibilidad de cara X por 1 y cara Y por 0.
			Si 3PI/2 (270º)
				Multiplicar la visibilidad de cara X por 0 y cara Y por 1.
			Codificar algoritmo que lo calcule.

QUADRANTE 2.
El punto medio se da en 240º (4PI / 3).

	1. Impacto en X.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del primer rayo hay que guardarlo en una variable específica.
		b. Cuanto menor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad = 100 % de la cara X.
			Si es 0.99 >>> visibilidad =   0 % de la cara X. 

	2. Impacto en Y.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del último rayo hay que guardarlo en una variable específica.
		b. Cuanto mayor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad =   0 % de la cara Y.
			Si es 0.99 >>> visibilidad = 100 % de la cara Y. 

	3. Ahora hay que calcular el factor de impresión de cada cara.
		a. Si el ángulo del jugador es 4PI/3 (240º), cada cara tendrá un 50 %.
		b. Algotitmo factor visibilización.
			Si 3PI/2 (270º)
				Multiplicar la visibilidad de cara X por 0 y cara Y por 1.
			Si M_PI (180º)
				Multiplicar la visibilidad de cara X por 1 y cara Y por 0.
			Codificar algoritmo que lo calcule.

QUADRANTE 3.
El punto medio se da en 135º (3PI / 4).

	1. Impacto en Y.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del primer rayo hay que guardarlo en una variable específica.
		b. Cuanto mayor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad =   0 % de la cara Y.
			Si es 0.99 >>> visibilidad = 100 % de la cara Y. 

	2. Impacto en X.
		a. Este punto de impacto también se guarda en la variable a->mlibx.sprite[c].x,
			y el del último rayo hay que guardarlo en una variable específica.
		b. Cuanto menor sea este valor, mayor será la visibilidad de esta cara
			del sprite.
			Si es 0.00 >>> visibilidad = 100 % de la cara X.
			Si es 0.99 >>> visibilidad =   0 % de la cara X. 

	3. Ahora hay que calcular el factor de impresión de cada cara.
		a. Si el ángulo del jugador es 3PI/4 (135º), cada cara tendrá un 50 %.
		b. Algotitmo factor visibilización.
			Si M_PI (180º)
				Multiplicar la visibilidad de cara X por 0 y cara Y por 1.
			Si M_PI_2 (90º)
				Multiplicar la visibilidad de cara X por 1 y cara Y por 0.
			Codificar algoritmo que lo calcule.
*/


