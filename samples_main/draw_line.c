#include "mlx.h"
#include <math.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	unsigned int	copy_nb;

	copy_nb = nb;
	if (copy_nb > 9)
		ft_putnbr(copy_nb / 10);
	ft_putchar(copy_nb % 10 + '0');
}

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX;
	double deltaY;
	int pixels;//
	double pixelX;
    double pixelY;

    deltaX = endX - beginX; // 10
    deltaY = endY - beginY; // 0
    pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY)); // 10
        // pixels ^ 2 = (deltaX ^ 2) + (deltaY ^ 2) >>> pixels = sqrt((10 * 10) + (0 * 0)) = sqrt(100) = 10
    pixelX = beginX; // 640
    pixelY = beginY; // 360
    deltaX /= pixels; // 1 >>> 10 / 10
    deltaY /= pixels; // 0 >>>  0 / 10
    while (pixels)
    {
        ft_putnbr(pixelX);
	    ft_putchar(',');
	    ft_putnbr(pixelY);
	    ft_putchar('\n');
        mlx_pixel_put(mlx, win, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
    return (1);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Draw Line");

    draw_line(mlx, win, 640, 360, 0, 0, 0xFFFFFF);
    draw_line(mlx, win, 10, 100, 20, 310, 0xAAFFFF); // This should create a white horizontal line about 10 pixels long.
    mlx_loop(mlx);
}
