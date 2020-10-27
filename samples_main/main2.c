/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 10:00:15 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 10:51:11 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     main(void)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "my_window");

	mlx_loop(mlx);
	return (0);
}
