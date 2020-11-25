/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 10:36:04 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/25 12:13:13 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct  s_vars {
    void	*mlx;
    void	*win;
}               t_vars;

int rgb_to_int_ligth(double r, double g, double b, double light)
{
    int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    color |= (int)(light * 255) << 32;
    return (color);
}

int rgb_to_int(double r, double g, double b)
{
    int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    printf("%d\n", color);
    return (color);
}

void    ft_fill_pixels(t_vars *param, int x, int y, long colour)
{
    
    int a;
    int b;

    a = x;
    while (a < x+30)
    {
        b = y;
        while (b < y+30)
        {
            mlx_pixel_put(param->mlx, param->win, a, b, colour);
            b++;
        }
        a++;
    }
}

int             main(void)
{
    t_vars  vars;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!");
	ft_fill_pixels(&vars, 300, 400, rgb_to_int(255, 255, 45));
    ft_fill_pixels(&vars, 400, 350, rgb_to_int_ligth(255, 255, 45, 45));
    ft_fill_pixels(&vars, 400, 300, rgb_to_int_ligth(200, 255, 45, 45));
    ft_fill_pixels(&vars, 400, 250, rgb_to_int_ligth(150, 255, 45, 45));
    ft_fill_pixels(&vars, 400, 200, rgb_to_int_ligth(100, 255, 45, 45));
    ft_fill_pixels(&vars, 400, 150, rgb_to_int_ligth(50, 255, 45, 45));
    ft_fill_pixels(&vars, 400, 100, rgb_to_int_ligth(0, 255, 45, 45));

    
    ft_fill_pixels(&vars, 300, 350, rgb_to_int(255, 255, 45));
    ft_fill_pixels(&vars, 300, 300, rgb_to_int(200, 255, 45));
    ft_fill_pixels(&vars, 300, 250, rgb_to_int(150, 255, 45));
    ft_fill_pixels(&vars, 300, 200, rgb_to_int(100, 255, 45));
    ft_fill_pixels(&vars, 300, 150, rgb_to_int(50, 255, 45));
    ft_fill_pixels(&vars, 300, 100, rgb_to_int(0, 255, 45));

    ft_fill_pixels(&vars, 250, 350 , 0x350CF2CDC);
    ft_fill_pixels(&vars, 250, 300 , 0x300CF2CDC);
    ft_fill_pixels(&vars, 250, 250 , 0x255CF2CDC);
    ft_fill_pixels(&vars, 250, 200 , 0x000CF2CDC);
    ft_fill_pixels(&vars, 250, 150 , 0xCF2CDC);
    
    ft_fill_pixels(&vars, 200, 350 , 0x350AAAFFF);
    ft_fill_pixels(&vars, 200, 300 , 0x300AAAFFF);
    ft_fill_pixels(&vars, 200, 250 , 0x255AAAFFF);
    ft_fill_pixels(&vars, 200, 200 , 0x000AAAFFF);
    ft_fill_pixels(&vars, 200, 150 , 0xAAAFFF);

/*  mlx_pixel_put(mlx, win, 150, 260 , 0xAAAFFF);
    mlx_pixel_put(mlx, win, 300, 250 , 0x00162DC2C);
    mlx_pixel_put(mlx, win, 250, 250 , 0x001CF2CDC);
    mlx_pixel_put(mlx, win, 200, 250 , 0x001AAAFFF);
    mlx_pixel_put(mlx, win, 150, 250 , 0xAAAFFF);
*/    mlx_loop(vars.mlx);
}
