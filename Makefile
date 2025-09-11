# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaland <agaland@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/09/10 12:16:56 by agaland          ###   ########.fr        #
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
SRC_EVENT = $(addprefix $(EVENT_DIR)/, )
#
RAYCASTER_DIR = raycaster
SRC_RAYCASTER = $(addprefix $(RAYCASTER_DIR)/, )
#
PARSER_DIR = parser
SRC_PARSER = $(addprefix $(PARSER_DIR)/, parsing parsing_utils map)
#
PLAYER_DIR = player
SRC_PLAYER = $(addprefix $(PLAYER_DIR)/, )
#
UTILS_DIR = utils
SRC_UTILS = $(addprefix $(UTILS_DIR)/, utils)

GNL_DIR = gnl
SRC_GNL = $(addprefix $(GNL_DIR)/, get_next_line_bonus get_next_line_utils_bonus)
#
SRCS ::= $(MAIN) $(SRC_EVENT) $(SRC_RAYCASTER) $(SRC_PARSER) $(SRC_PLAYER) $(SRC_UTILS) $(SRC_GNL)
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
INC_FLAG += -I $(LIBFT_DIR)/$(INC_DIR)
LIB_FLAG = -lft -lX11 -lXext -lm 
#
#----------------------------MISC----------------------------------------------#
#----------------------------RULES---------------------------------------------#
#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@
#
lib:	$(LIBFT) minilbx
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
minilbx:
	@$(MAKE) -C $(MINILBX_DIR)
#
$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LIB_FLAG) -o $(NAME)
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
debug: $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LIB_FLAG) -o $(NAME)
	@echo "$(NAME) created !"
#
-include $(DEPENDS)
#
.PHONY: all clean libclean fclean re
#----------------------------TEXT----------------------------------------------#

#
#----------------------------MISC----------------------------------------------#
#
