/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:00:17 by stempels          #+#    #+#             */
/*   Updated: 2025/09/17 16:17:29 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
/*_______________________________MACRO________________________________________*/
# define SIZE_MOD 32
# define ESC_KEY 65307
# define LEFT_KEY 0xff51
# define UP_KEY 0xff52
# define RIGHT_KEY 0xff53
# define DOWN_KEY 0xff54
# define FLOOR_COLOR 0xedf0f5
# define WALL_COLOR 0x428715
# define PLAYER_COLOR 0xfa3737
# define RAY_COLOR 0xb366ff
# define SPEED 0.5
# define SPEED_RATIO 2
# define TURN_SPEED (10 * M_PI / 180)
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

typedef struct		s_dda
{
	int				map[2];
	int				step[2];
	double			dir[2];
	double			raydir[2];
	double			d_dist[2];
	double			side_dist[2];
	double			angle;
	double			limit;
}					t_dda;

typedef struct		s_ray
{
	int				side;
	double			dist;
	unsigned int	color;
}					t_ray;
/*_______________________________FUNCT________________________________________*/
#endif
