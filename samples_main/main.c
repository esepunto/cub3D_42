/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 10:21:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 10:50:59 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <unistd.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	ft_putchar('X');
//	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xAAAFFF);
	return (0);
}

int		main()
{
	void	*mlx_ptr;// Es un void según se indica en el man. Para iniciar MiniLibX
	void	*win_ptr;// Void para iniciar ventana
	void	*img;
/*	int		i;
	int		j;
*/
	mlx_ptr = mlx_init();// Engancha coon la MiniLibX. Es lo primero que hay que hacer.
	img = mlx_new_image(mlx_ptr, 1920, 1980);
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "my_first_window of all my life its call Sandra. BUENORRA!!!");// Man para gestionar ventanas en "man /usr/sharre(¡/man/man3/mlx_new_window.1" (new window, clear window, destry window)
/*	i = 0;
	while (i <= 499)
	{
		j = 0;
		while (j < 999)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFFFFFF);
			mlx_pixel_put(mlx_ptr, win_ptr, j, i, 0xFFFFFF);
			j++;
		}
		if (i == 499)
			i = 0;
		else
			i++;
	}
*/	mlx_string_put(mlx_ptr, win_ptr, 50, 100, 0xFFFFFF, "ESTE JUEVES, PA CUENCA!!");
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_mouse_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);//Para gestionar el loop de eventos (interactuaciones del usuario en la ventana)
}
