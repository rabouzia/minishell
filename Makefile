# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junsan <junsan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 19:03:01 by junsan            #+#    #+#              #
#    Updated: 2024/06/10 17:46:35 by junsan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell
BONUS 	= minishell_bonus
OS		= $(shell uname)

CC		= cc
LIBFT 	= libft/libft.a
IFLAGS 	:= -I ./includes/ -I ./libft/includes/

CFLAGS 	= -Wall -Wextra -Werror -g3

SRC_DIR = src
PARSING_DIR = $(SRC_DIR)/parsing
BUILT_IN_DIR = $(SRC_DIR)/built_in
UTILS_DIR = $(SRC_DIR)/utils
INIT_DIR = $(SRC_DIR)/init
SIGNAL_DIR = $(SRC_DIR)/signal
EXECUTE_DIR = $(SRC_DIR)/exec
OBJ_DIR = obj

SRC 	= minishell.c
INIT	= init_minishell.c
PARSING	= process_input.c tokenize.c parsing.c prints.c get_type.c arg_parse.c 	\
		get_file_list.c 														\
		/utils/parsing_utils.c /utils/tokenize_utils.c /utils/tokenize_utils_2.c\
		/utils/get_file_list_utils.c /utils/redir_handler.c 					\
		/utils/type_functions.c
UTILS	= string_utils.c
SIGNAL	= handler_signal.c
EXECUTE = execute.c
#BUILT_IN = built_in.c file_dir_operations.c	\

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))
SRCS += $(addprefix $(PARSING_DIR)/, $(PARSING))
SRCS += $(addprefix $(INIT_DIR)/, $(INIT))
SRCS += $(addprefix $(UTILS_DIR)/, $(UTILS))
SRCS += $(addprefix $(SIGNAL_DIR)/, $(SIGNAL))
SRCS += $(addprefix $(EXECUTE_DIR)/, $(EXECUTE))
#SRCS += $(addprefix $(BUILT_IN_DIR)/, $(BUILT_IN))

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

ifeq ($(OS), Linux)
	LD_FLAGS = -lreadline
else ifeq ($(OS), Darwin)
	LD_FLAGS = -L$(shell brew --prefix readline)/lib -lreadline
	IFLAGS += -I $(shell brew --prefix readline)/include
endif

vpath %.c ./src/

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFALGS) -o $@ $(OBJS) $(LIBFT) $(LD_FLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT): 
	@make -C libft/

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean: clean
	@make -C libft/ fclean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
