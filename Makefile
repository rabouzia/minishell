# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junsan <junsan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:03:01 by junsan            #+#    #+#              #
#    Updated: 2024/05/13 18:37:29 by junsan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell
BONUS 	= minishell_bonus

CC		= cc
LIBFT 	= libft/libft.a
IFLAGS 	= -I ./includes/ -I ./libft/includes/

CFLAGS 	= -Wall -Wextra -Werror -g

SRC 	= minishell.c init_minishell.c

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

vpath %.c ./src/

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFALGS) -o $@ $(OBJS) $(LIBFT)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT): 
	@make -C libft/

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean: clean
	@make -C libft/ fclean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
