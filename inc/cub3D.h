/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:44:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/25 16:14:15 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE
# include "libft.h"
# include "raycaster.h"
# include "mlx.h"
# include "error.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/time.h>

/**/
/*_______________________________MACRO________________________________________*/
# define SUCCES 0
# define ERROR 1
# define FOV 66
# define EAST 0
# define SOUTH 90
# define WEST 180
# define NORTH 270
# define WIDTH 1920
# define HEIGHT 1080
# define COLL_DIST 0.1
# define MINI_SIZE 16
# define MINI_BORDER_L 16
# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLYSH_CMD 2
# define MLX_SYNC_WIN_CMD_COPLETED 3
/**/
/*____________COLORS_*/
# define RAY_COLOR 0xb366ff
# define PLAYER_COLOR 0xfa3737
# define WALL_COLOR 0xff003600
# define FLOOR_COLOR 0xffe8ddb3
# define MINI_BACKGROUND 0x4a4946

/*_______________________________STRUCT_______________________________________*/

typedef struct			s_game
{
	int				**map;
	int				max_x;
	int				max_y;
	int				screen_width;
	int				screen_height;
	int				minimap;
	int				mini_size;
	int				mini_width;
	int				mini_height;
	int				fov;
	int				show_fov;
	int				show_fps;
	int				show_col;
	unsigned long int		start_time;
	unsigned long int		old_time;
	unsigned int	default_color[4];
	double			frametime;
	struct s_texture	*texture[4];
	struct s_player	*player;
	struct s_data	*data;
	struct s_config	*config;
}					t_game;

typedef	struct		s_config
{
	char			*first_map;
	char			*textures_path[4];
	int 			floor_rgb[3];
	int 			ceiling_rgb[3];
	int				player_count;
	bool			map_end;
}					t_config;

typedef	struct		s_texture
{
	void			*wall;
	char			*addr_w;
	int				height;
	int				width;
	int				bpp;
	int				l_length;
	int				endian;
}					t_texture;

typedef	struct		s_player
{
	float 			facing;
	float			pos[2];
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
	FILLED
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
int			process_config(int fd, t_game *game);
int			parse_config(char *line, int *arr, t_game *game);
int			parse_line(t_game *game, char *line, int *i, int type);
int			fill_texture(t_game *game, char *line, int *i, int type);
int			check_rgb(char *line, int *i, t_config *config, int type);
int 		parse_rgb(char **start, int *count, int type, t_config *config);
int			process_map_recursive(int fd, t_game *game);
int			skip_and_save_type(int type, int *arr, int *i);
int			ft_isblank(char c);
int			check_map_closure(t_game *game);
int			floodfill(t_game *game, int pos_y, int pos_x, char flag);
int			init_game(t_game *game, int rows);
int			init_map(t_game *game, char *line, int curr_row, int line_lenght);
int			compare_types(char *line_pos);
int			ft_strcmp(const char *s1, const char *s2);
bool		is_texture(int type);
bool		valid_file_extension(char *filename, char *ext, char del);
bool		detect_content(char *line, char *first_char);
bool		config_completed(int *parsed_elements);
void		init_config(t_game *game);

/*________________HOOK___*/
int			key_handler(int keycode, t_game *game);
void	toggle_handler(t_game *game, int keycode);
/*________________PLAYER*/
void	move_handler(t_game *game, int keycode);
/*________________RAYCAST*/
int			cub3d(t_game *game);
int			game_loop(t_game *game);
void		dda_operation(t_game *game, float facing);
void		dda_collision(t_game *game, float move[2], float camera);
void		block_put(t_data *data, int pos[3], int size, unsigned int color);
void		px_put(t_data *data, int x, int y, unsigned int color);
void		draw_player(t_game *game, t_data *data, unsigned int color);
void		draw_minimap(t_game *game, t_data *data);
void		draw_wall(t_game *game, t_dda *dda, t_ray *ray);
void		draw_line(t_game *game, t_dda *dda, t_ray *ray);
void		refresh_screen(t_game *game);
float		safe_angle_add(float *angle, float mod);
double		get_angle(int type, int facing);
/*________________UTILS__*/
void		print_map(int **matrix, int height, int width);
void		print_int_arr(int *arr, int len);
void		ft_error(char *msg, char *var);
void		free_map(int **array, int	size);
void		cleanup_game(t_game *game);
void		gnl_cleanup(char *line);
void		free_config(t_config *config);
void		malloc_exit(t_game *game, char *line);
void		get_fps(t_game *game);
unsigned int	convert_int(int rgb[3]);
int			clean_all(t_game *game);
int		close_all(t_game *game);
#endif
