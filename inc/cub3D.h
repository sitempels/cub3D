/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:44:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/16 10:57:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE
# include "libft.h"
# include "raycaster.h"
# include "mlx.h"
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
# define FOV 66
# define NORTH (3 * M_PI / 2)
# define SOUTH (M_PI / 2)
# define EAST 0
# define WEST (M_PI)
# define WIDTH 1080
# define HEIGHT 912


/*_______________________________STRUCT_______________________________________*/

typedef struct		s_game
{
	int				**map;
	int				max_x;
	int				max_y;
	int				minimap;
	double			screen_width;
	double			screen_height;
	double			fov;
	struct s_player	*player;
	struct s_data	*data;
}					t_game;

typedef	struct		s_config
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	int 			*floor_color;
	int 			*ceiling_color;
}					t_config;

typedef	struct		s_player
{
	double 			facing;
	double			pos[2];
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

typedef enum e_config_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}			t_config_type;

/*_______________________________FUNCTION_____________________________________*/
/*________________PARSING*/
char		*ft_strnstr_end(const char *haystack, const char *needle, size_t len);
int			parse_file(int fd, t_game *game);
int			process_map_recursive(int fd, t_game *game, int *rows, int *max_len);
int			check_line(char *line);
int			init_game(t_game *game, int rows, int max_len);
int			init_map(t_game *game, char *line, int curr_row, int line_lenght);
int			ft_strcmp(const char *s1, const char *s2);
bool		valid_file_extension(char *filename, char *ext, char del);
void		init_player(t_game *game, int y, int x, double facing);

/*________________PLAYER_*/
/*________________RAYCAST*/
int			close_all(t_game *game, t_data *data, int status);
int			key_handler(int keycode, t_game *game);
int			display_handler(t_game *game);
int			game_loop(t_game *game);
void		img_put(t_data *data, float x, float y, unsigned int color);
void		px_put(t_data *data, int x, int y, unsigned int color);
void		safe_angle_add(double *angle, double mod);
void		draw_player(t_game *game, t_data *data, unsigned int color);
void		draw_minimap(t_game *game, t_data *data);
double		dda_operation(t_game *game, double facing);
/*________________UTILS__*/
void		print_map(int **matrix, int height, int width);
void		print_int_arr(int *arr, int len);
void		cleanup_game(t_game *game);
void		gnl_cleanup(char *line);

#endif
