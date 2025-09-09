/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:44:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/09 14:15:41 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "raycaster.h"
# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <math.h>
/**/
/*_______________________________MACRO________________________________________*/
/*_______________________________STRUCT_______________________________________*/

typedef struct		s_game
{
	int				**map;
	int				max_x;
	int				max_y;
	int				fov;
	struct s_player	*player;
	struct s_data	*data;
}					t_game;

typedef	struct		s_player
{
	float 			facing;
	float			pos_x;
	float			pos_y;
}					t_player;
/*_______________________________ENUM_________________________________________*/
typedef enum e_type
{
	EMPTY = 0,
	WALL,
	N,
	E,
	S,
	W,
}			t_type;
/*_______________________________FUNCTION_____________________________________*/
/*________________PARSING*/
/*________________PLAYER_*/
/*________________RAYCAST*/
int			close_all(t_game *game, t_data *data, int status);
int			key_handler(int keycode, t_game *game);
int			display_handler(t_game *game, int max_x, int max_y);
void	img_put(t_data *data, float x, float y, unsigned int color);
/*________________UTILS__*/
#endif
