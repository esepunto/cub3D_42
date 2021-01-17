NAME	=	cub3D

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

LIBS	=	libft/libft.a libft/ft_printf/libftprintf.a libmlx.dylib 

OBJECTS	=	$(SRCS:.c=.o)

LINKS	=	-I ./mlx_beta -L ./mlx_beta -lmlx -framework OpenGL -framework AppKit

RM		=	rm -f

.PHONY:		all
all:		make_libs $(NAME)

.PHONY:	make_libs
make_libs:
			@make -C libft
			@make -C libft/ft_printf
			@make -C mlx_beta
			@mv ./mlx_beta/libmlx.dylib ./

$(NAME):	$(OBJECTS)
			$(CC) $(LINKS) $(LIBS) $(SRCS) -o $(NAME) 

clean:
			$(RM) $(OBJECTS)
			@make clean -C libft
			@make clean -C libft/ft_printf
			@make clean -C mlx
			@make clean -C mlx_beta

fclean:		clean
			$(RM) $(NAME)
			@make fclean -C libft
			@make fclean -C libft/ft_printf
			rm -f libmlx.dylib 

re: fclean all

norma:
		norminette cub3d.c
		norminette srcs/
		norminette libft/
		norminette includes/

play:
		make
		./cub3D maps/valid_RGB_001.cub

save:
		make
		./cub3D maps/valid_RGB_001.cub --save

