# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junsan <junsan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 02:27:45 by junsan            #+#    #+#              #
#    Updated: 2024/06/25 14:14:05 by junsan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= cc
IFLAG	= -I ./includes/
CFLAGS	= -Wall -Wextra -Werror -g3

SRC		= \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c		\
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c				\
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c			\
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c			\
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c	\
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c			\
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 							\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c					\
		gnl/get_next_line.c	gnl/get_next_line_utils.c							\

SRC_DIR = ./src/

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

vpath %.c ./src/

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) -rcs $@ $?

%.o: %.c
	$(CC) -c $(CFLAGS) $(IFLAG) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
