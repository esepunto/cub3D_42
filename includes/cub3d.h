/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:42:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/04 13:40:43 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# define KEY_ESC		53
# define KEY_LOOK_RIGHT	124
# define KEY_LOOK_LEFT	123
# define KEY_MOVE_FRONT	13
# define KEY_MOVE_BACK	1
# define KEY_MOVE_LEFT	0
# define KEY_MOVE_RIGHT	2
# define FOV			60 * M_PI / 180

typedef struct  s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_minilibx
{
	void	*mlx;
	void	*win;
	t_data	img;
}				t_minilibx;

typedef struct	s_map
{
	char	**maze;
	size_t	col;
	int		row;
	int		num_players;
	int		first_line;
	int		nbrlines;
}				t_map;

typedef struct s_lanzarayos
{
	double	modulo;
	double	xplyr;
	double	yplyr;
	double	dirplyr;
	double	movspeed;
	double	rotspeed;
	double	lasttime;
	double	delta;
	double	xray;
	double	yray;
	double	anglray;
	int		quadrant;
	double	xincrease;
	double	yincrease;
	double	xdist2coord;
	double	ydist2coord;
	double	distance;
	int		initwall;
	int		endwall;
	double	staturewall;
	int		nbr_ray;
	bool	xhit;
	bool	yhit;
	int		wallcolor;
	int		keycode;
}				t_lanzaray;


typedef struct	s_readconfig
{
	int			xrendersize;
	int			yrendersize;
	int			red[2];
	int			green[2];
	int			blue[2];
	char		*wall[8];
	char		*wall_texture[8];
	int			nb_wrd_param;
	int			final_line_params;
	uint32_t	ceilcolor;
	uint32_t	floorcolor;
	t_map		map;
}				t_config;

typedef struct	s_cub3d
{
	t_config	fconf;
	t_minilibx	mlibx;
	t_lanzaray	steal;
}				t_cub3d;

int				main(int argc, char **argv);
void			init_struct(t_cub3d *a);
void			open_fconfig(char *conf_file, t_cub3d *a);
void			calc_fconfig(char *conf_file, t_cub3d *a);
void			save_fconfig(char *conf_file, t_cub3d *a);
void			isthisaparam(t_cub3d *a);
char			*look4texture(char *id, size_t idlen, t_cub3d *a);
void			manage_params(t_cub3d *a);
void			review_walls(int c, t_cub3d *a);
void			review_cefl(int c, t_cub3d *a);
void			review_res(int c, t_cub3d *a);
void			review_params(t_cub3d *a);
void			cleantexture(int c, t_cub3d *a);
void			check_nbr(int c, t_cub3d *a);
void			isdigit_str(char *nbr);
void			extract_rgb(int c, t_cub3d *a);
void			is_repeat(int	m, t_cub3d *a, const char *id);
void			frstlinemaze(t_cub3d *a);
void			manage_map(t_cub3d *a);
void			forbidd_chr(char c);
int				nbr_plyrs(int i, int j, t_cub3d *a);
void			review_maze(t_cub3d *a);
void			surrounded(int i, size_t j, char **maze, t_cub3d *a);
void			maze_algorithm(t_cub3d *a);
uint32_t		ceilfloorcolor(int c, t_cub3d *a);

void			init_window(t_cub3d *a);
int				caress_key(int keycode, t_cub3d *a);
int				closed(t_cub3d *a);

void			my_mlx_pixel_put(t_cub3d *a, int x, int y, int color);
void			draw_background(t_cub3d *a);

/*
void			draw_minimap(t_cub3d *a);
void			put_pixel_minimap(int x, int y, t_cub3d *a, long color);
void			draw_player(t_cub3d *a);
void			draw_line(t_cub3d *a, int beginX, int beginY, int endX, int endY, int color);
*/

int				raycast(t_cub3d *a);
int				draw(t_cub3d *a);
int				teclado(int keycode, t_cub3d *a);
void			calc_texture(t_cub3d *a);
void			calc_wallimpact(t_cub3d *a);
void			gofront(t_cub3d *a);
void			goback(t_cub3d *a);
void			goright(t_cub3d *a);
void			goleft(t_cub3d *a);


int				msg_err(char *error);
void			print_fconfig(t_cub3d *a);
void			delmem(t_cub3d *a);
void			print_struct(t_cub3d *a);

#endif
