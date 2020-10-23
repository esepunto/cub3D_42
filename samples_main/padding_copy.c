#include "../cub3d.h"
#include <stdio.h>

// Alignment requirements
// (typical 32 bit machine)

// char     1 byte
// short int  2 bytes
// int     4 bytes
// double    8 bytes

// structure A
typedef struct structa_tag
{
char    c;
short int  s;
} structa_t;

// structure B
typedef struct structb_tag
{
short int  s;
char    c;
int     i;
} structb_t;

// structure C
typedef struct structc_tag
{
char    c;
double   d;
int 	 s;
} structc_t;

// structure D
typedef struct structd_tag
{
double	d;
int 	i;
char	c;
} t_structd;

// structure E
typedef struct structe_tag
{
char	c;
int	 	s;
double	d;
} structe_t;

// structure F
typedef struct structf_tag
{
char	c;
char	e;
int	 	s;
double	d;
} structf_t;

// structure G
typedef struct structg_tag
{
char	c;
char	e;
char	f;
int	 	s;
double	d;
} structg_t;

// structure H
typedef struct structh_tag
{
char	c;
char	e;
char	f;
char	a;
int	 	s;
double	d;
} structh_t;

// structure I
typedef struct structi_tag
{
char	c;
char	e;
char	f;
char	a;
int	 	s;
double	d;
void	*i;
} structi_t;

// structure J
typedef struct structj_tag
{
char		c;
char		e;
char		f;
char		a;
int	 		s;
double		d;
char		i;
} structj_t;

// structure K
typedef struct structk_tag
{
char			c;
char			e;
char			f;
char			a;
int	 			s;
double			d;
int				i;
} structk_t;

// structure L
typedef struct structl_tag
{
char	c;
} structl_t;

// structure M
typedef struct structm_tag
{
char	c;
char	s;
} structm_t;

// structure N
typedef struct structn_tag
{
void	*c;
} structn_t;

// structure O
typedef struct structo_tag
{
void	*c;
void	*s;
} structo_t;

// structure P
typedef struct structp_tag
{
void	*c;
char	a;
void	*s;
} structp_t;

// structure Q
typedef struct structq_tag
{
void	*c;
void	*s;
char	a;
} structq_t;

// structure R
typedef struct structr_tag
{
char	a;
void	*c;
void	*s;
} structr_t;

int main()
{
	t_structd	*hola;

	if (!(hola = malloc(sizeof(t_structd))))
		return (0);
/*	printf("sizeof(structa_t) = %lu\n", sizeof(structa_t));
	printf("sizeof(structb_t) = %lu\n", sizeof(structb_t));
	printf("sizeof(structc_t) = %lu\n", sizeof(structc_t));
*/	printf("sizeof(t_structd) = %lu\n", sizeof(t_structd));
/*	printf("sizeof(structe_t) = %lu\n", sizeof(structe_t));
	printf("sizeof(structf_t) = %lu\n", sizeof(structf_t));
	printf("sizeof(structg_t) = %lu\n", sizeof(structg_t));
	printf("sizeof(structh_t) = %lu\n", sizeof(structh_t));
	printf("sizeof(structi_t) = %lu\n", sizeof(structi_t));
	printf("sizeof(structj_t) = %lu\n", sizeof(structj_t));
	printf("sizeof(structk_t) = %lu\n", sizeof(structk_t));
	printf("sizeof(structl_t) = %lu\n", sizeof(structl_t));
	printf("sizeof(structm_t) = %lu\n", sizeof(structm_t));
	printf("sizeof(structn_t) = %lu\n", sizeof(structn_t));
	printf("sizeof(structo_t) = %lu\n", sizeof(structo_t));
	printf("sizeof(structp_t) = %lu\n", sizeof(structp_t));
	printf("sizeof(structq_t) = %lu\n", sizeof(structq_t));
	printf("sizeof(structr_t) = %lu\n", sizeof(structr_t));
*/	hola->i = 6;
	hola->c = 'd';
	hola->d = 234;
	free(hola);
	ft_printf("i vale %d y c vale %c\n", hola->i, hola->c);
	free(hola);
	ft_printf("hola vale %lu\n", sizeof(&hola));
/*	free(hola);
	ft_printf("hola vale %lu\n", sizeof(&hola));
*/	system ("leaks tutorial");
	return (0);
}
