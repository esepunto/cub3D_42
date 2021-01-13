/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:18:28 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/13 02:29:00 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_buffer
{
	double	angle;
	bool	ray;
}				t_buffer;

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

typedef struct	s_sprite
{
	double		angle;
	double		distance;
	double		stature;
	double		width_span;
	double		yfloat;
	double		xfloat;
	double		ystep;
	double		xstep;
	int			init;
	int			end;
	int			sequence;
	int			xpos;
	int			ypos;
	int			ysprite;
	int			xsprite;
	int			point;
	int			palette;
	int			first_ray;
	int			last_ray;
	int			current_ray;
	int			rayinit;
	int			midray;
	double		midangle;
	bool		view;
	t_buffer	*buff;
}				t_sprite;

typedef struct	s_minilibx
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_texture	xpmwall[5];
	int			sizex;
	int			sizey;
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
	int		nbr_sprite;
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
	t_sprite	sprite[25];
	bool		save_bmp;
}				t_cub3d;

#endif
