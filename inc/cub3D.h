/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:44:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/08 18:21:56 by agaland          ###   ########.fr       */
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
/*________________UTILS__*/
#endif
