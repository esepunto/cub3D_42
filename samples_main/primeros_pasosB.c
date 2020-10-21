#include "mlx.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 300

typedef struct  s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
}   t_img;

typedef struct  s_mlx
{
    void    *mlx_ptr;
    void    *win;
    t_img   img;
    int     line_length;
    int     endian;
}   t_mlx;

int 	main ()
{
	t_mlx   mlx; // Aquí primero creo mi estructura que contendrá todas las "cosas MLX"
	int     count_w;
	int     count_h;

		// Primero necesitas llamar a mlx_init y almacenar su valor de retorno.
	mlx.mlx_ptr = mlx_init ();
	// Ahora haz lo mismo con mlx_new_window
	mlx.win = mlx_new_window(mlx. mlx_ptr ,WIN_WIDTH, WIN_HEIGHT, " Un ejemplo simple " );
	// Una vez más con mlx_new_image
	mlx.img.img = mlx_new_image(mlx.mlx_ptr ,WIN_WIDTH, WIN_HEIGHT);
	/*
	 Ahora la parte importante:
	 mlx_get_data_addr devolverá un carácter * que es 4 veces el (ancho * alto) de su imagen.
	 Porque ? Déjame explicarte: este carácter * representará tu imagen, píxel a píxel,
	 y los valores de esta matriz son los colores. Es por eso que la matriz es 4 veces más grande:
	 necesita 4 caracteres para codificar el color de cada píxel (uno para rojo, verde y azul) y otro para el alfa.
	 Pero ... no es muy conveniente, ¿verdad? Así que aquí está mi pequeño truco: lanzas
	 mlx_get_data_addr como int * y almacenarlo en int *.
	 De esta manera, la matriz tendrá exactamente el mismo tamaño que su ventana, y cada índice
	 representará un color completo de un píxel!
	*/
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, &mlx.img.line_length, &mlx.img.endian);
	/*
	 Ahora solo un pequeño ejemplo: aquí hay un bucle que dibujará cada píxel que
	 tienen un ancho impar en blanco y los que tienen un ancho par en negro.
	*/
	count_h = - 1;
    while (++count_h < (WIN_HEIGHT * 4))
	{
		count_w = -1 ;
		while (++count_w < WIN_WIDTH)
		{
			if (count_w % 2 == 0)
				/*
				 Como puede ver aquí en lugar de usar la función mlx_put_pixel
				 Solo asigno un color a cada píxel uno por uno en la imagen,
				 y la imagen se imprimirá de una vez al final del ciclo.
				 Ahora bien, una cosa que hay que entender aquí es que estás trabajando en un modelo unidimensional.
				 matriz, mientras que su ventana es (obviamente) bidimensional.
				 Entonces, en lugar de tener datos [altura] [ancho] aquí, tendrá lo siguiente
				 fórmula: [altura actual * ancho máximo + ancho actual] (como puede ver a continuación)
				*/
				mlx.img.addr[count_h * WIN_WIDTH + count_w] = 14396716;
			else
				mlx.img.addr[count_h * WIN_WIDTH + count_w] = 3093151;
		}
	}
	// ¡ Ahora solo tienes que imprimir la imagen usando mlx_put_image_to_window!
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx. mlx_ptr);
	return (0);
}