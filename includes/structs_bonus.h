/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:18:28 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/21 18:44:58 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef struct	s_buffer
{
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
	double		midangle;
	int			init;
	int			end;
	int			xpos;
	int			ypos;
	int			ysprite;
	int			xsprite;
	int			point;
	int			palette;
	int			current_ray;
	int			rayinit;
	int			rayend;
	int			midray;
	bool		view;
	bool		killer;
	t_buffer	*buff;
}				t_sprite;

typedef struct	s_minilibx
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_texture	xpmwall[4];
	t_texture	object[2];
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
	double	xincrease;
	double	yincrease;
	double	distance;
	double	staturewall;
	double	xwallhit;
	double	ywallhit;
	double	ytexturefloat;
	double	ysteptexture;
	double	ystep;
	double	xstep;
	int		quadrant;
	int		initwall;
	int		endwall;
	int		nbr_ray;
	int		xtexture;
	int		ytexture;
	int		wall;
	int		count;
	int		point;
	int		aux;
	int		palette;
	bool	hit;
	bool	xhit;
	bool	yhit;
	double	*angbuf;
	int		keycode[160];
}				t_raycast;

typedef struct	s_readconfig
{
	int			xrendersize;
	int			yrendersize;
	int			red[2];
	int			green[2];
	int			blue[2];
	int			nb_wrd_param;
	int			final_line_params;
	int			ceilcolor;
	int			floorcolor;
	char		*wall[9];
	char		*wall_texture[9];
	t_map		map;
}				t_config;

typedef struct	s_cub3d
{
	bool		save_bmp;
	int			life;
	t_config	fconf;
	t_raycast	rayc;
	t_minilibx	mlibx;
	t_sprite	sprite[25];
}				t_cub3d;

#endif
