/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:44:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/10 00:20:03 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>

/**/
/*_______________________________MACRO________________________________________*/

# define CELL_TYPE "01NSEW "
# define SPACE " "
/*_______________________________STRUCT_______________________________________*/

typedef struct		s_game
{
	int				**map;
	int				fov;
	struct s_player	*player;
}					t_game;

typedef	struct		s_player
{
	float 			facing;
	int				x;
	int				y;
}					t_player;
/*_______________________________ENUM_________________________________________*/
typedef enum e_type
{
	EMPTY = -1,
	FLOOR,
	WALL,
	N,
	E,
	S,
	W,
}			t_type;
/*_______________________________FUNCTION_____________________________________*/
/*________________PARSING*/
int		parse_file(int fd, t_game *game);
int		process_map_recursive(int fd, int ***matrix, int *rows, int *max_len);

bool	valid_file_extension(char *filename, char *ext);
int		allocate_matrix(int ***matrix, int rows);
int		init_matrix(int ***matrix, char *line, int max_len, int curr_row, int line_lenght);
char	*ft_strnstr_end(const char *haystack, const char *needle, size_t len);

/*________________PLAYER_*/
/*________________RAYCAST*/
/*________________UTILS__*/
void	print_map(int **matrix, int height, int width);

#endif
