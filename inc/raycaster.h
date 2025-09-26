/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:00:17 by stempels          #+#    #+#             */
/*   Updated: 2025/09/26 11:20:17 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
/*_______________________________MACRO________________________________________*/
# define SIZE_MOD 32
# define MINI_BORDER_SIZE 32
# define SPEED 7.0
# define TURN_SPEED 120.0
/*____________KEY_*/
# define ESC_KEY 65307
# define A_KEY 0x61
# define D_KEY 0x64
# define F_KEY 0x66
# define G_KEY 0x67
# define H_KEY 0x68
# define S_KEY 0x73
# define W_KEY 0x77
# define COMMA_KEY 0x2c
# define LEFT_KEY 0xff51
# define RIGHT_KEY 0xff53
/*_______________________________STRUCT_______________________________________*/
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bpp;
	int		l_length;
	int		endian;
}	t_data;

typedef struct s_dda
{
	int				map[2];
	int				step[2];
	float			dir[2];
	float			raydir[2];
	float			d_dist[2];
	float			side_dist[2];
	float			angle;
	float			limit;
}	t_dda;

typedef struct s_ray
{
	int				side;
	int				x;
	float			dist;
	unsigned int	color;
}	t_ray;
/*_______________________________FUNCT________________________________________*/
#endif
