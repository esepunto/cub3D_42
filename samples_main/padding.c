#include "../cub3d.h"
#include <stdio.h>

// Alignment requirements
// (typical 32 bit machine)

// char     1 byte
// short int  2 bytes
// int     4 bytes
// double    8 bytes

// structure D
typedef struct structd_tag
{
	double	d;
	int 	i;
	char	c;
} t_structd;


int main()
{
	t_structd	*hola;

	if (!(hola = malloc(sizeof(t_structd))))
		return (0);
	printf("sizeof(t_structd) = %lu\n", sizeof(t_structd));
	hola->i = 6;
	hola->c = 'd';
	hola->d = 234;
	free(hola);
	ft_printf("i vale %d y c vale %c\n", hola->i, hola->c);
	free(hola);
	ft_printf("hola vale %lu\n", sizeof(&hola));
	free(hola);//Puedo elimiarlo y no hay leaks
	system ("leaks tutorial");
	return (0);
}
