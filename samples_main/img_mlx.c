#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

int close(void *param)
{
    (void)param;
    exit(0);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Create Image");

    /*
    ** This image is 230.400 pixels (640x360). (Maybe I changed its in line 28 and 29 to test behaviours.)
    ** It's equal to 921.600 bytes: 4 bytes by pixel because pixel is an int.
    */
    int width_x = 640;
    int height_y = 360;
    void *image;
    image = mlx_new_image(mlx, width_x, height_y);
        
    /* 
    ** To get information related to the image.
    **
    ** The function will also return a char * which points to
    ** the beginning of the memory address for the actual pixel data.
    */
    int pixel_bits;
    int line_bytes;
    int endian;
    char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    printf("pixel_bits: %d\n", pixel_bits);
    printf("line_bytes: %d\n", line_bytes);
    printf("endian: %d\n", endian);

    
    int color = 0xEFABCD;

    if (pixel_bits != 32)
        color = mlx_get_color_value(mlx, color);

    int pixel;
    for(int y = 100; y < height_y; ++y)
    for(int x = 50; x < width_x; ++x)
    {
        pixel = (y * line_bytes) + (x * 4);
        if (endian == 1)        // Most significant (Alpha) byte first
        {
            buffer[pixel + 0] = (color >> 24);
            buffer[pixel + 1] = (color >> 16) & 0xFF;
            buffer[pixel + 2] = (color >> 8) & 0xFF;
            buffer[pixel + 3] = (color) & 0xFF;
        }
        else if (endian == 0)   // Least significant (Blue) byte first
        {
            buffer[pixel + 0] = (color) & 0xFF;
            buffer[pixel + 1] = (color >> 8) & 0xFF;
            buffer[pixel + 2] = (color >> 16) & 0xFF;
            buffer[pixel + 3] = (color >> 24);
        }
    }
    /*
    ** To display the image.
    */
    mlx_put_image_to_window(mlx, win, image, 0, 0);

    mlx_hook(win, 17, int x_mask, close(void *param), void *param);

    mlx_loop(mlx);
    
    system("leaks -fullContent a.out");
}