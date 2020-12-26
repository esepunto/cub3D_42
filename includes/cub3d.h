/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:42:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/26 05:50:21 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_beta/mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# define KEY_ESC			53
# define KEY_ROTATE_RIGHT	124
# define KEY_ROTATE_LEFT	123
# define KEY_MOVE_FRONT		13
# define KEY_MOVE_BACK		1
# define KEY_MOVE_LEFT		0
# define KEY_MOVE_RIGHT		2

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_texture_xpm
{
	void	*mlx;
	char	*relative_path;
	int		width;
	int		height;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct	s_minilibx
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_texture	xpmwall[4];
	t_texture	sprite;
	int			sizex;
	int			sizey;
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

typedef struct	s_raycast
{
	double	modulo;
	double	xplyr;
	double	yplyr;
	double	dirplyr;
	double	rush;
	double	rotspeed;
	double	lasttime;
	double	delta;
	double	xray;
	double	yray;
	double	anglray;
	double	fov;
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
	double	xwallhit;
	double	ywallhit;
	int		xtexture;
	int		ytexture;
	double	ytexturefloat;
	double	ysteptexture;
	int		wall;
	int		count;
	int		point;
	int		aux;
	int		palette;
	double	ystep;
	double	xstep;
	double	xdistance;
	double	ydistance;
	bool	hit;
}				t_raycast;

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
	t_raycast	rayc;
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
int				ceilfloorcolor(int c, t_cub3d *a);

void			save_textures(t_cub3d *a);
void			calc_texturing(t_cub3d *a);

void			calc_vertangl(t_cub3d *a);

void			init_window(t_cub3d *a);
void			rescale_screen(t_cub3d *a);
int				caress_key(int keycode, t_cub3d *a);
int				close_window(t_cub3d *a);

void			brushstroke(int x, int y, t_cub3d *a, int color);
void			pointillism(t_cub3d *a);
void			paintwalls(t_cub3d *a, int point);
void			half_lower_wall(t_cub3d *a);
void			half_upper_wall(t_cub3d *a);

int				raycast(t_cub3d *a);
void			throw_rays(t_cub3d *a);
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
void			print_textures(t_cub3d *a);
void			print_texture(t_cub3d *a);
void			print_divide(double x, int y);
void			print_direction(t_cub3d *a);
void			print_wall(t_cub3d *a);
void			print_color(t_cub3d *a);
void			print_addr(t_cub3d *a);

#endif
