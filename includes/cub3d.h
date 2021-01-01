/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:42:55 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/01 18:45:26 by ssacrist         ###   ########.fr       */
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

typedef struct	s_sprite_xpm
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
	double	angle;
	double	dist_sprite;
	double	stature;
	double	yfloat;
	double	xfloat;
	double	ystep;
	int		initsprite;
	int		endsprite;
	int		sequence;
	int		xpos;
	int		ypos;
	int		ysprite;
	int		y;
	int		xaux;
	int		x;
	int		count;
	int		aux;
	int		point;
	int		quadrant;
	bool	xhit;
	bool	yhit;
}				t_sprite;


typedef struct	s_minilibx
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_texture	xpmwall[5];
	int			sizex;
	int			sizey;
	int			nbr_sprite;
	t_sprite	sprite[1024];
}				t_minilibx;

typedef struct	s_map
{
	char	**maze;
	size_t	col;
	int		row;
	int		num_players;
	int		num_sprites;
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
	double	xray;
	double	yray;
	double	anglray;
	double	fov;
	int		quadrant;
	double	xincrease;
	double	yincrease;
	double	distance;
	int		initwall;
	int		endwall;
	double	staturewall;
	int		nbr_ray;
	bool	xhit;
	bool	yhit;
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
	int			ceilcolor;
	int			floorcolor;
	t_map		map;
}				t_config;

typedef struct	s_cub3d
{
	t_config	fconf;
	t_raycast	rayc;
	t_minilibx	mlibx;
}				t_cub3d;

int				main(int argc, char **argv);
void			open_fconfig(char *conf_file, t_cub3d *a);
void			manage_params(t_cub3d *a);
void			review_params(t_cub3d *a);
void			check_nbr(int c, t_cub3d *a);
void			isdigit_str(char *nbr);
void			extract_rgb(int c, t_cub3d *a);
void			manage_map(t_cub3d *a);
void			maze_algorithm(t_cub3d *a);
int				ceilfloorcolor(int c, t_cub3d *a);

void			save_textures(t_cub3d *a);

void			init_window(t_cub3d *a);
int				caress_key(int keycode, t_cub3d *a);
int				close_window(t_cub3d *a);

void			throw_rays(t_cub3d *a);
void			calc_texturing(t_cub3d *a);
void			pointillism(t_cub3d *a);

void			found_sprite(t_cub3d *a);
void	allocate_sprites(t_cub3d *a);
void	save_sprites(t_cub3d *a);
void	clean_sprites(t_cub3d *a);
void	sort_sprites(t_cub3d *a);
void	calc_stature_sprite(t_cub3d *a, int point);
void	paintsprites(t_cub3d *a, int point);

int				msg_err(char *error);
void			delmem(t_cub3d *a);

void			print_fconfig(t_cub3d *a);
void			print_struct(t_cub3d *a);
void			print_textures(t_cub3d *a);
void			print_texture(t_cub3d *a);
void			print_divide(double x, int y);
void			print_direction(t_cub3d *a);
void			print_wall(t_cub3d *a);
void			print_color(t_cub3d *a);
void			print_addr(t_cub3d *a);
void			print_sprites(t_cub3d *a);

#endif
