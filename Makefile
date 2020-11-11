NAME	=	cub3D

CC		=	gcc -Wall -Wextra -Werror -g

#SRCS	=	srcs/*.c

SRCS	=	cub3d.c \
			srcs/file_config/readnsave_fconfig.c \
			srcs/file_config/params/errors_params.c \
			srcs/file_config/params/look4params.c \
			srcs/file_config/map/manage_map.c \
			srcs/file_config/map/map_algorithm.c \
			utils/messages.c \
			utils/del_mem.c \
			utils/tests.c

#MAIN	=	./samples_main/main_split.c
#MAIN	=	./srcs/2read_map/read_map.c
#MAIN	=	./samples_main/perror.c
#MAIN	=	./samples_main/structs_edramire.c
#MAIN	=	./samples_main/padding_structs.c
#MAIN	=	./samples_main/rgb_to_hex.c
#MAIN	=	./samples_main/main_correccion.c
#MAIN	=	./samples_main/main_printf.c
#MAIN	=	./samples_main/gccc.c
#MAIN	=	./samples_main/gnl_main.c
#MAIN	=	./samples_main/primeros_pasosA.c
#MAIN	=	./samples_main/primeros_pasosB.c
#MAIN	=	./samples_main/endian.c
#MAIN	=	./samples_main/event_main.c //No funciona aún
#MAIN	=	./samples_main/hook.c #Error
#MAIN	=	./samples_main/img_mlx.c
#MAIN	=	./samples_main/rgb_to_int.c
#MAIN	=	./samples_main/put_pixels.c
#MAIN	=	./samples_main/draw_line.c
#MAIN	=	./samples_main/image1.c
#MAIN	=	./samples_main/main.c
#MAIN	=	./samples_main/main2.c

LIBS	=	libft/libft.a \
			mlx/libmlx.a \
			libft/ft_printf/libftprintf.a

OBJECTS	=	$(SRCS:.c=.o)

LINKS	=	-I ./mlx -L ./mlx -lmlx -framework OpenGL -framework AppKit

RM		=	rm -f

all: $(NAME)

$(NAME):	$(OBJECTS)
			@make -C libft
			@make -C libft/ft_printf
			@make -C mlx
			$(CC) $(LINKS) $(LIBS) $(OBJECTS) -o $(NAME)
#			$(CC) $(LINKS) $(SRCS) $(LIBS) -o $(NAME)

clean:
			$(RM) $(OBJECTS)
			@make clean -C libft
			@make clean -C libft/ft_printf
			@make clean -C mlx


fclean:		clean
			$(RM) $(NAME)
			@make fclean -C libft
			@make fclean -C libft/ft_printf


re: fclean all
