# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 13:05:39 by mde-maga          #+#    #+#              #
#    Updated: 2024/09/15 13:16:13 by mde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c ft_bzero.c ft_isalnum.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcat.c \
ft_strlcpy.c ft_toupper.c ft_strlen.c ft_tolower.c ft_strchr.c ft_strrchr.c \
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c get_next_line.c get_next_line_utils.c ft_printf.c \
ft_arguments.c ft_putchar.c ft_putnbr_u.c ft_putnbr.c ft_put_hex.c \
ft_putpointer.c ft_putstr.c ft_strcmp.c

SRCB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
ft_lstmap.c

OBJECTS = ${SRC:.c=.o}
BOBJECTS = ${SRCB:.c=.o}

CC = @cc

CFlAGS = -Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJECTS)
		@ar -crs $(NAME) $(OBJECTS)

bonus: $(NAME) $(BOBJECTS)
		@ar -crs $(NAME) $(BOBJECTS)

clean:
	@rm -f $(OBJECTS)
	@rm -f $(BOBJECTS)

fclean:		clean
	@rm -f $(NAME)

re:		fclean all

.PHONY: all bonus clean fclean re
