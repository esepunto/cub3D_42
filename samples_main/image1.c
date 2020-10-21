#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_memdel(void **a)
{
	if (!a || !*a)
		return ;
	free(*a);
	*a = NULL;
}

/*
** Gets the data address of the current image.
**
** @param  void *img_ptr        the image instance;
** @param  int  *bits_per_pixel a pointer to where the bpp is written;
** @param  int  *size_line      a pointer to where the line is written;
** @param  int  *endian         a pointer to where the endian is written;
** @return char *               the memory address of the image.
*/
char    * mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);

/*
** Puts an image to the given window.
**
** @param  void *mlx_ptr the mlx instance;
** @param  void *win_ptr the window instance;
** @param  int  x        the x location of where the image ought to be placed;
** @param  int  y        the y location of where the image ought to be placed;
** @return int           has no return value (bc).
*/
int     mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);

/*
** Converts a png file to a new image instance.
**
** @param  void *mlx_ptr   the mlx instance;
** @param  char *filename  the file to load;
** @param  int  *width     a pointer to where the width ought to be written;
** @param  int  *height    a pointer to where the height ought to be written;
** @warn   mem_leak        this function has a memory leak, try using xpm
**                         instead;
** @return void *          the image instance.
*/
void    *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);

int     main(void)
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *relative_path = "./samples_xpm/test.xpm";
    int     img_width;
    int     img_height;
    
//    char    *info_img;
//    int     bits_pixel;
//    int     size_line;
//    int     endian;
    int     c = 0;
    static int     x = 3;
    static int     y = 2;

    
    mlx = mlx_init();
    win = mlx_new_window(mlx, 500, 500, "buenorra's window to put image on");
    relative_path = "./samples_xpm/event_main.xpm";
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 10, 80);
    mlx_destroy_image(mlx, img);
    
    
    relative_path = "./samples_xpm/test.xpm";
    while (c < 150)
    {
        img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
        mlx_put_image_to_window(mlx, win, img, 250+y, 250+x);
        mlx_put_image_to_window(mlx, win, img, 250-y, 250-x);
        mlx_put_image_to_window(mlx, win, img, 250+y, 250-x);
        mlx_put_image_to_window(mlx, win, img, 250-y, 250+x);
        mlx_put_image_to_window(mlx, win, img, 250+x, 250+y);
        mlx_put_image_to_window(mlx, win, img, 250-x, 250-y);
        mlx_put_image_to_window(mlx, win, img, 250+x, 250-y);
        mlx_put_image_to_window(mlx, win, img, 250-x, 250+y);        
    //    mlx_destroy_image(mlx, img);
    //    printf("%d", c);
    //    y = y + (x/y);
    //    x = (x + y);
        x += x;
        y += y;
    //    x = y+x;
        c++;
    //    mlx_clear_window(mlx, win);
    }    

/*
    relative_path = "./samples_xpm/test2.xpm";
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, win, img, 10, 50);
    c = 0;
    mlx_destroy_image(mlx, img);
    printf("%d", c);
*/

    mlx_loop(mlx);
    system("leaks a.out");
}