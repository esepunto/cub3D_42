#include "mlx.h"

int rgb_to_int(double r, double g, double b)
{
    int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Draw Pixel");

    mlx_pixel_put(mlx, win, 640/2, 360/2, 0xFF0000);
    mlx_pixel_put(mlx, win, (640/2)+10, 360/2, 16711680);
    mlx_pixel_put(mlx, win, (640/2)+20, 360/2, rgb_to_int(0, 0, 255));

    mlx_loop(mlx);
}