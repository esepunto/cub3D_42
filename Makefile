NAME	=	cub3D

CC		=	gcc -Wall -Wextra -Werror -g

SRCS	=	cub3d.c \
			srcs/file_config/readnsave_fconfig.c \
			srcs/file_config/params/manage_params.c \
			srcs/file_config/params/review_params.c \
			srcs/file_config/params/rgb.c \
			srcs/file_config/map/manage_map.c \
			srcs/file_config/map/maze_algorithm.c \
			srcs/window/manage_window.c \
			srcs/window/vangoghs_turn.c \
			srcs/raycast/raycast.c \
			srcs/raycast/movement.c \
			srcs/raycast/textures.c \
			srcs/raycast/sprite.c \
			srcs/utils.c 

LIBS	=	libft/libft.a \
			libft/ft_printf/libftprintf.a \
			libmlx.dylib 
#			mlx/libmlx.a



OBJECTS	=	$(SRCS:.c=.o)

LINKS	=	-I ./mlx_beta -L ./mlx_beta -lmlx -framework OpenGL -framework AppKit


RM		=	rm -f

all: $(NAME)

$(NAME):	$(OBJECTS)
			@make -C libft
			@make -C libft/ft_printf
			@make -C mlx_beta
			@mv ./mlx_beta/libmlx.dylib ./
#			$(CC) $(LINKS) $(LIBS) $(OBJECTS) -o $(NAME)
			$(CC) $(LINKS) $(SRCS) $(LIBS) -o $(NAME)

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

norma:	norminette srcs/
		norminette libft/
		norminette includes/

