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
	printf("sizeof(t_structd) ocupa %lu\n", sizeof(t_structd));
	hola->i = 6;
	hola->c = 'd';
	hola->d = 234;
	printf("i == %d /-/ c == %c /-/ d == %f \n", hola->i, hola->c, hola->d);
	printf("&hola ocup %lu\n", sizeof(&hola));
	printf("hola ocupa %lu\n", sizeof(hola));
	ft_printf("hola->i ocupa %u\n", sizeof(hola->i));
	ft_printf("hola->c ocupa %u\n", sizeof(hola->c));
	ft_printf("hola->d ocupa %u\n", sizeof(hola->d));
	printf("hola->i == %d\n", hola->i);
	printf("hola->c == %c\n", hola->c);
	printf("hola->d == %f\n", hola->d);
	free(hola);
	printf("hola->i == %d\n", hola->i);
	printf("hola->c == %c\n", hola->c);
	printf("hola->d == %f\n", hola->d);
	system ("leaks tutorial");
	return (0);
}
