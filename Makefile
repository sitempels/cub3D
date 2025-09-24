# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaland <agaland@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/09/22 21:45:37 by agaland          ###   ########.fr        #
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
CCFLAGS = -Wall -Wextra -Werror -fPIE
debug: CCFLAGS = -g3 -fPIE
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
SRC_RAYTRACER = $(addprefix $(RAYTRACER_DIR)/, display_handler display_handler_utils dda_operation dda_utils draw_wall)
#
PARSER_DIR = parser
SRC_PARSER = $(addprefix $(PARSER_DIR)/, parsing parsing_utils config config_utils map map_utils floodfill)
#
PLAYER_DIR = player
SRC_PLAYER = $(addprefix $(PLAYER_DIR)/,)
#
UTILS_DIR = utils
SRC_UTILS = $(addprefix $(UTILS_DIR)/, utils)

GNL_DIR = gnl
SRC_GNL = $(addprefix $(GNL_DIR)/, get_next_line_bonus get_next_line_utils_bonus)
#
SRCS ::= $(MAIN) $(SRC_EVENT) $(SRC_RAYTRACER) $(SRC_PARSER) $(SRC_PLAYER) $(SRC_UTILS) $(SRC_GNL)
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
LIB_FLAG = -lft -lmlx -lX11 -lXext -lm -lz
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
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) -L$(MINILBX_DIR) $(LIB_FLAG) -o $(NAME)
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
re: fclean all
#
debug: fclean $(OBJ) $(LIB) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) -L$(MINILBX_DIR) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) created !"
#
.PHONY: all clean libclean fclean re
#----------------------------TEXT----------------------------------------------#

#
#----------------------------MISC----------------------------------------------#
#
