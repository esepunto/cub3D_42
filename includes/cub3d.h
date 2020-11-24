/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:42:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/24 09:10:09 by ssacrist         ###   ########.fr       */
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

typedef struct	s_minilibx
{
	void	*mlx;
	void	*win;
	void	*img;
}				t_minilibx;

typedef struct	s_raycasting
{
	double	xpos;
	double	ypos;
	double	xdir;
	double	ydir;
	double	xplane;
	double	yplane;
	double	time;
	double	oldtime;
	double	xcamera;
	double	xraydir;
	double	yraydir;
	double	xmap;
	double	ymap;
	double	xsidedist;
	double	ysidedist;
	double	xdeltadist;
	double	ydeltadist;
	double	perpwalldist;
	int		xstep;
	int		ystep;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	frametime;
	double	movespeed;
	double	rootspeed;
	double	xolddir;
	double	yolddir;
}				t_raycast;

typedef struct	s_map
{
	char	**maze;
	size_t	col;
	int		row;
	int		num_players;
	int		first_line;
}				t_map;

typedef struct	s_readconfig
{
	int		xrendersize;
	int		yrendersize;
	int		red[2];
	int		green[2];
	int		blue[2];
	char	*wall[8];
	char	*wall_texture[8];
	int		nb_wrd_param;
	int		final_line_params;
	t_map	map;
}				t_config;

typedef struct	s_cub3d
{
	t_config	fconf;
	t_minilibx	mlibx;
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
int				nbr_plyrs(char c);
void			review_maze(t_cub3d *a);
void			surrounded(int i, size_t j, char **maze, t_cub3d *a);
void			maze_algorithm(t_cub3d *a);
int				msg_err(char *error);
void			print_fconfig(t_cub3d *a);
void			delmem(t_cub3d *a);

#endif
