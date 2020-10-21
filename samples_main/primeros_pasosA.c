#include "../cub3d.h"

typedef struct  s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
//    int *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x;
    int     y;
    unsigned int color;
    
    color = 0x00DBAD2C;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 300, "Hello world!"); 
    img.img = mlx_new_image(mlx, 500, 300);
    /*mlx_get_data_addr devuelve un char* que es 4 veces el (alto*ancho) de la imagen.
    Este char* representa la imagen, pixel a pixel y los valores de esta matriz son los colores
    Por eso la matriz es 4 veces mas grande, necesita 4 caracteres para codificar el color de cada pixel (rojo, verde, azul) y otro para alfa.
    El truco es lanzar mlx_get_data_addr como int* y almacenarlo como int*. Y asi la matriz tendra el mismo tamanio que su ventana.*/
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    x = 0;
    while (x <= 500)
    {
        y = 0;
        while(y <= 300)
        {
            my_mlx_pixel_put(&img, x, y, color);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    ft_printf("bits per pixel: %-10.8d -- ", img.bits_per_pixel);
    ft_printf("color: %X", color);
    mlx_loop(mlx);
}


/*
int main(void)
{
    void *mlx;
    t_data img;
    mlx = mlx_init();
    img.img = mlx_new_image(mlx, 1920, 1080);
// ** After creating an image, we can call `mlx_get_data_addr`, we pass ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will ** then be set accordingly for the *current* data address. 
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    mlx_loop(mlx);
}
*/