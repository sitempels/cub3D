# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaland <agaland@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 10:47:36 by stempels          #+#    #+#              #
#    Updated: 2025/09/08 18:06:44 by agaland          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += --silent
#
NAME = cub3D 
TYPE = EXEC
#----------------------------COMPILER------------------------------------------#
CC = clang
CCFLAGS = -Wall -Wextra -Werror
CPPFLAGS = $(INC_FLAG)
#
#----------------------------LINKER--------------------------------------------#
#----------------------------DEBUG---------------------------------------------#
#----------------------------MAIN----------------------------------------------#
#----------------------------SRC-----------------------------------------------#
SRC_DIR = src
SRC = $(addprefix src/, $(addsuffix .c, main)) 
#
#----------------------------OBJ-----------------------------------------------#
OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#
#----------------------------LIB-----------------------------------------------#
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_FLAG = -I $(LIBFT_DIR)/$(INC_DIR)
#
#----------------------------HEADER--------------------------------------------#
INC_DIR = inc
INC_FLAG += -I$(INC_DIR)
#
#----------------------------RULES---------------------------------------------#
all: $(NAME)
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(CPPFLAGS) -c $< -o $@
#
lib:	$(LIBFT) 
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
#
$(NAME): $(OBJ) $(LIBFT) minilibx
	$(CC) $(CCFLAGS) $(OBJ) -L$(LIBFT_DIR) -lX11 -lXext -lm -lft -o $@
	@echo "$(NAME) $(GREEN)created !$(NC)"
#
minilibx: 
	@$(MAKE) -C minilibx_linux
#
clean: libclean
	rm -rf $(OBJ_DIR)
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
libclean:
	$(MAKE) clean -C $(LIBFT_DIR)	
	rm -rf $(LIBFT)
#
fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)	
	@echo "$(NAME) $(GREEN)$@ed !$(NC)"
#
re: fclean all
#
.PHONY: all clean libclean fclean re design
#----------------------------TEXT----------------------------------------------#
GREEN=\033[0;32m
NC=\033[0m
#
#----------------------------MISC----------------------------------------------#
#
