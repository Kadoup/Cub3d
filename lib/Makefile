# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 12:19:27 by tjourdan          #+#    #+#              #
#    Updated: 2025/09/09 17:51:57 by tjourdan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

INCLUDE	= -I./

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g

SRC		=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_itoa.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_abs.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstutils.c \
			ft_lstprevlast.c \
			ft_printf_utils2.c \
			ft_printf_utils.c \
			ft_printf.c \
			get_next_line.c

OBJ_DIR = obj

OBJ		= $(addprefix $(OBJ_DIR)/, ${SRC:.c=.o})


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

all:	${NAME}

${NAME}:	${OBJ}
	ar rc ${NAME} ${OBJ}

bonus :
	$(MAKE) BONUS=1

clean:
	rm -f ${OBJ}
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re