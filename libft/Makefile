# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 12:54:03 by ssacrist          #+#    #+#              #
#    Updated: 2020/12/27 00:05:59 by ssacrist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

SRC			=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isblank.c \
				ft_isspace.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_islower.c \
				ft_isprint.c \
				ft_isupper.c \
				ft_memccpy.c \
				ft_memcmp.c \
				ft_memchr.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				*ft_itoa.c \
				**ft_split.c \
				*ft_strmapi.c \
				*ft_strjoin.c \
				*ft_strtrim.c \
				*ft_substr.c \
				ft_chekext.c \
				ft_delmatrix.c \
				ft_countchr.c \
				ft_cntwrds.c \
				ft_delinitblanks.c \
				ft_delendblanks.c \
				ft_delinitendblanks.c \
				ft_replacetabs.c \
				ft_hex2int.c \
				ft_rgb2hex.c \
				get_next_line.c

SRC_BONUS	=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

OBJ			=	$(SRC:.c=.o)

OBJ_BONUS 	= 	$(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rcs $(NAME) $(OBJ) $(LIBS)

clean:
		rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus:	$(OBJ_BONUS)
		ar rcs $(NAME) $(OBJ_BONUS)
