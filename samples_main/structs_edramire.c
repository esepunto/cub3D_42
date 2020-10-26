#include "../cub3d.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

typedef struct	s_tag {
	char	a_char;
	int		a_int;
	double	a_double;
}				t_tag;

void print_t_tag(t_tag tag)
{
	printf("a_char: %2c | a_int: %8i | a_double: %16f\n", tag.a_char, tag.a_int, tag.a_double);
	printf("a_char: %02x | a_int: %08x | a_double: %016lx\n", (short int)tag.a_char, tag.a_int, *((size_t *)&tag.a_double));
}

int		main(void)
{
	t_tag	local;
	t_tag	*pointer;

	// Local es una variable local y su tamaño depende de la variables que
	// conforman la estructura
	printf("local size: %ld\n", sizeof(local));
	// Pointer es un puntero y su tamaño siempre es 8 Bytes
	printf("pointer size: %ld\n", sizeof(pointer));
	printf("char size: %ld | int size: %ld | double size: %ld\n", sizeof(char), sizeof(int), sizeof(double));

	pointer = malloc(sizeof(t_tag));
	if (pointer == NULL)
		return (-1);
	// El tamaño de pointer sigue siendo 8 Bytes pero ahora contienes una
	// referencia a un zona de memoria reservada del tamaño de t_tag
	printf("Direccion inicial la memoria reservada:    %p\n", pointer);
	printf("Direccion inicial de la variable a_char:   %p\n", &pointer->a_char);
	printf("Direccion inicial de la variable a_int:    %p\n", &pointer->a_int);
	printf("Direccion inicial de la variable a_double: %p\n", &pointer->a_double);
	pointer->a_int = 18;
	pointer->a_double = 23.45;
	pointer->a_char = 'C';
	printf("\nprint *pointer: \n");
	print_t_tag(*pointer);

	// Una variable de estructura no necesita realizar una reserva de memoria
	// Hagamos un truco para copiar los valores
	memcpy(&local, pointer, sizeof(t_tag));
	printf("\nprint local: \n");
	print_t_tag(local);

	// Igual podemos acceder a los valores de local y modificarlos
	local.a_char = 'E';
	local.a_double = 0.25;
	local.a_int = 27;

	printf("\nprint local: \n");
	print_t_tag(local);

	// Un puntero no es mas que una forma de acceder a una variable definida
	// en memoria. Si cambiamos el tipo del puntero podemos acceder a la
	// informacion de otra manera

	memcpy(pointer, "EDUARDO RAMIREZ", sizeof(t_tag));
	printf("%s\n", (char *)pointer);
	printf("\nprint *pointer: \n");
	print_t_tag(*pointer);

	// Una vez liberada una reserva de memoria, aun cuando la direccion sigue
	// siendo valida, seria incorrecto tratar de manipular esa direccion de
	// memoria
	free(pointer);
	return (0);
}
