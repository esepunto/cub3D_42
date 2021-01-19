NAME	=	cub3D

NAME_BONUS	=	cub3D_bonus

CC		=	gcc -Wall -Wextra -Werror -g

SRCS	=	cub3d.c \
			srcs/file_config/load_fconfig.c \
			srcs/file_config/params_manage.c \
			srcs/file_config/params_review.c \
			srcs/file_config/rgb_colors.c \
			srcs/file_config/map_manage.c \
			srcs/file_config/maze_algorithm.c \
			srcs/window/manage_window.c \
			srcs/window/vangogh_turn.c \
			srcs/window/picasso_turn.c \
			srcs/raycast/init_raycast.c \
			srcs/raycast/movement.c \
			srcs/raycast/textures.c \
			srcs/raycast/sprites_manage.c \
			srcs/raycast/sprites_calcs.c \
			srcs/screenshot/gerdataro_turn.c

SRCS_BONUS	=	cub3d_bonus.c \
				srcs_bonus/file_config/load_fconfig_bonus.c \
				srcs_bonus/file_config/params_manage_bonus.c \
				srcs_bonus/file_config/params_review_bonus.c \
				srcs_bonus/file_config/rgb_colors_bonus.c \
				srcs_bonus/file_config/map_manage_bonus.c \
				srcs_bonus/file_config/maze_algorithm_bonus.c \
				srcs_bonus/window/dead_bonus.c \
				srcs_bonus/window/manage_window_bonus.c \
				srcs_bonus/window/vangogh_turn_bonus.c \
				srcs_bonus/window/picasso_turn_bonus.c \
				srcs_bonus/raycast/init_raycast_bonus.c \
				srcs_bonus/raycast/movement_bonus.c \
				srcs_bonus/raycast/textures_bonus.c \
				srcs_bonus/raycast/sprites_manage_bonus.c \
				srcs_bonus/raycast/sprites_calcs_bonus.c \
				srcs_bonus/screenshot/gerdataro_turn_bonus.c

LIBS	=	libft/libft.a libft/ft_printf/libftprintf.a libmlx.dylib 

OBJECTS	=	$(SRCS:.c=.o)

OBJECTS_BONUS	=	$(SRCS_BONUS:.c=.o)

LINKS	=	-I ./mlx_beta -L ./mlx_beta -lmlx -framework OpenGL -framework AppKit

RM		=	rm -f

.PHONY:		all
all:		make_libs $(NAME)

.PHONY:		bonus
bonus:		make_libs $(NAME_BONUS)

.PHONY:		make_libs
make_libs:
			@make -C libft
			@make -C libft/ft_printf
			@make -C mlx_beta
			@mv ./mlx_beta/libmlx.dylib ./

$(NAME):	$(OBJECTS)
			$(CC) $(LINKS) $(LIBS) $(SRCS) -o $(NAME)

$(NAME_BONUS):	$(OBJECTS_BONUS)
				$(CC) $(LINKS) $(LIBS) $(SRCS_BONUS) -o $(NAME_BONUS)

clean:
			$(RM) $(OBJECTS)
			$(RM) $(OBJECTS_BONUS)
			@make clean -C libft
			@make clean -C libft/ft_printf
			@make clean -C mlx
			@make clean -C mlx_beta

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(NAME_BONUS)
			@make fclean -C libft
			@make fclean -C libft/ft_printf
			rm -f libmlx.dylib 

re: fclean all

norma:
		norminette cub3d.c
		norminette srcs/
		norminette libft/
		norminette includes/

norma_bonus:
		norminette cub3d_bonus.c
		norminette srcs_bonus/
		norminette libft/
		norminette includes/

play:
		make
		./cub3D maps/valid_RGB_001.cub

play_bonus:
		make bonus
		./cub3D_bonus maps/valid_RGB_001.cub

save:
		make
		./cub3D maps/valid_RGB_001.cub --save

save_bonus:
		make bonus
		./cub3D_bonus maps/valid_RGB_001.cub --save

delgerda:
		$(RM) gerda_taro.bmp gerda_taro_bonus.bmp
