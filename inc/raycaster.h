/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:00:17 by stempels          #+#    #+#             */
/*   Updated: 2025/09/09 13:33:59 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
/*_______________________________MACRO________________________________________*/
# define SIZE_MOD 64
# define WIDTH 1920
# define HEIGHT 1080
# define ESC_KEY 65307
# define UP_KEY 0xff52
# define DOWN_KEY 0xff54
# define LEFT_KEY 0xff51
# define RIGHT_KEY 0xff53
# define EMPTY_COLOR 0xedf0f5
# define WALL_COLOR 0x428715
# define PLAYER_COLOR 0xfa3737
# define SPEED_FORWARD 2
# define SPEED_BACKWARD 1
/*_______________________________STRUCT_______________________________________*/
typedef struct		s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bpp;
	int		l_length;
	int		endian;
}					t_data;

typedef struct		s_point
{
	int	x;
	int	y;
	int	color;
}					t_point;
/*_______________________________FUNCT________________________________________*/
#endif
