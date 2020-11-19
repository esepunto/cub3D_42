/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:42:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/19 14:44:22 by ssacrist         ###   ########.fr       */
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

typedef struct	s_raycast
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
}				t_rayc;

typedef struct	s_map
{
	char		**map;
	size_t		col;
	int			row;
	int			num_players;
	int			first_line;
}				t_map;

typedef struct	s_readconfig
{
	char	*res;
	int		xrendersize;
	int		yrendersize;
	char	*wallno;
	char	*wallno_texture;
	char	*wallso;
	char	*wallso_texture;
	char	*wallea;
	char	*wallea_texture;
	char	*wallwe;
	char	*wallwe_texture;
	char	*sprite;
	char	*sprite_texture;
	char	*ceil;
	char	*flr;
	int		ceilclr;
	int		red[2];
	int		green[2];
	int		blue[2];
	int		flrclr;
	int		init_id[8];
	char	*wall[8];
	char	*wall_texture[8];
	int		nb_wrd_param;
	int		repeat[8];
	int		final_line_params;
	t_map	map;
	t_map	rotate_map;
}				t_config;

typedef struct	s_cub3d
{
	t_config	fconf;
}				t_cub3d;

int		main(int argc, char **argv);
int		msg_err(char *error);
void	init_struct(t_cub3d *a);
void	open_fconfig(char *conf_file, t_cub3d *a);
void	calc_fconfig(char *conf_file, t_cub3d *a);
void	save_fconfig(char *conf_file, t_cub3d *a);
void	find_params(t_cub3d *a);
char	*look4_id(char *id, t_cub3d *a);
int		jump_sp(int i, t_cub3d *a);
char	*extract_path(const char *id, t_cub3d *a, int m);
void	is_repeat(int	m, t_cub3d *a, const char *id);
char	*look4_texture(char *str, char *id);
void	isthisaparam(t_cub3d *a);
void	review_params(t_cub3d *a);
void	review_walls(int c, t_cub3d *a);
void	review_cefl(int c, t_cub3d *a);
void	extract_rgb(int c, t_cub3d *a);
void	check_nbr(int c, t_cub3d *a);
void	review_res(int c, t_cub3d *a);
void	isdigit_str(char *color);
void	check_nbr(int c, t_cub3d *a);
int		look4color(int c, t_cub3d *a);



void	print_fconfig(t_cub3d *a);






void	find_walls(t_cub3d *a);
void	find_walls_2(t_cub3d *a);









void	check_nbr(int c, t_cub3d *a);




void 	find_map(t_cub3d *a);
void	is_space2map(t_cub3d *a);
void	check_line_map(int line, t_cub3d *a);
void	check_frst_column(t_cub3d *a);
void 	review_map_horiz(t_cub3d *a);
void	forbidd_chr(char c);
void	repeat_chr(int i, size_t j, t_cub3d *a);
void	map_algorithm(t_cub3d *a);

void	surrounded(int i, size_t j, char **map);


void	print_fconfig(t_cub3d *a);
void	del_mem(t_cub3d *a);
void	del_mem_fconf(t_cub3d *a);

#endif
