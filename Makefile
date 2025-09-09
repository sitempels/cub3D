# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/09/09 11:04:03 by stempels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += --silent
#
NAME_PROJECT = cub3D 
NAME = $(NAME_PROJECT)
debug: NAME = $(addprefix debug_, $(NAME_PROJECT))
TYPE = EXEC
#----------------------------COMPILER------------------------------------------#
CC = cc
debug: CC = gcc 
CCFLAGS = -Wall -Wextra -Werror
debug: CCFLAGS = -g3
CPPFLAGS = $(INC_FLAG)
#
#----------------------------LINKER--------------------------------------------#
#----------------------------DEBUG---------------------------------------------#
#----------------------------HEADER--------------------------------------------#
INC_DIR = inc
INC_FLAG = -I$(INC_DIR)
#
#----------------------------SRC-----------------------------------------------#
MAIN = main
SRC_DIR = src
#
EVENT_DIR = event
SRC_EVENT = $(addprefix $(EVENT_DIR)/,)
#
RAYTRACER_DIR = raytracer
SRC_RAYTRACER = $(addprefix $(RAYTRACER_DIR)/, display_handler display_handler_utils)
#
PARSER_DIR = parser
SRC_PARSER = $(addprefix $(PARSER_DIR)/,)
#
PLAYER_DIR = player
SRC_PLAYER = $(addprefix $(PLAYER_DIR)/,)
#
UTILS_DIR = utils
SRC_UTILS = $(addprefix $(UTILS_DIR)/,)
#
SRCS ::= $(MAIN) $(SRC_EVENT) $(SRC_RAYTRACER) $(SRC_PARSER) $(SRC_PLAYER) $(SRC_UTILS)
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS))) 
#
#----------------------------OBJ-----------------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#
#----------------------------LIB-----------------------------------------------#
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILBX_DIR = minilibx_linux
MINILBX = $(MINILBX_DIR)/libmlx_Linux.a
INC_FLAG += -I $(LIBFT_DIR)/$(INC_DIR) -I $(MINILBX_DIR)
LIB += $(LIBFT) $(MINILBX)
LIB_FLAG = -lX11 -lXext -lm -lz
#
#----------------------------MISC----------------------------------------------#
#----------------------------RULES---------------------------------------------#
#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	echo $(SRC)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@
#
lib: $(LIB)
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(MINILBX):
	@$(MAKE) -C $(MINILBX_DIR)
#
$(NAME): $(OBJ) $(LIB) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIB) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) $(GREEN)created !$(NC)"

run: $(NAME)
	@./$(NAME)
#
leak: debug
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes --suppressions=./valgrind.supp ./debug_$(NAME_PROJECT)
#
vgdb: debug
	@valgrind --vgdb-error=0 --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=./valgrind.supp ./debug_$(NAME_PROJECT)
#
clean: libclean
	rm -rf $(OBJ_DIR) $(DEPENDS)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
libclean:
	$(MAKE) clean -C $(LIBFT_DIR)	
	$(MAKE) clean -C $(MINILBX_DIR)
	rm -rf $(LIBFT)
#
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)	
	rm -rf $(NAME)
	rm -rf $(addprefix debug_, $(NAME))
	$(MAKE) fclean -C $(LIBFT_DIR)	
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
re: all
#
debug: fclean $(OBJ) $(LIB) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIB) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) created !"
#
.PHONY: all clean libclean fclean re
#----------------------------TEXT----------------------------------------------#

#
#----------------------------MISC----------------------------------------------#
#
