/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:56:44 by stempels          #+#    #+#             */
/*   Updated: 2025/09/24 16:13:40 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_angle(int type, int facing)
{
	double	res;

	if (type == 0)
	{
		if (facing == NORTH || facing == SOUTH)
			res = 0;
		else if (facing == EAST)
			res = 1;
		else if (facing == WEST)
			res = -1;
		else
			res = cosf(facing * M_PI / 180);
	}
	if (type == 1)
	{
		if (facing == EAST || facing == WEST)
			res = 0;
		else if (facing == NORTH)
			res = -1;
		else if (facing == SOUTH)
			res = 1;
		else
			res = sinf(facing * M_PI / 180);
	}
	return (res);
}

void	refresh_screen(t_game *game)
{
	int				i;
	int				j;
	unsigned int	color;

	i = -1;
	while (++i <= game->screen_width)
	{
		j = -1;
		while (++j <= game->screen_height)
		{
			if (game->minimap)
			{
				if (i < game->mini_width)
					if (j < game->mini_height + game->mini_size)
						j = game->mini_height + game->mini_size;
			}
			if (j < game->screen_height / 2)
				color = convert_int(game->config->floor_rgb);
			if (j >= game->screen_height / 2)
				color = convert_int(game->config->ceiling_rgb);
			px_put(game->data, i, j, color);
		}
	}
	return ;
}

void	draw_line(t_game *game, t_dda *dda, t_ray *ray)
{
	float	pos[2];
	float	p_px[2];
	float	dist[2];

	pos[0] = game->player->pos[0] * game->mini_size;
	pos[1] = game->player->pos[1] * game->mini_size;
	dist[0] = 0;
	dist[1] = 0;
	while ((ray->side == 0 && dist[0] < ray->dist * game->mini_size)
		|| (ray->side == 1 && dist[1] < ray->dist * game->mini_size))
	{
		p_px[0] = pos[0] + (dist[0] * dda->raydir[0]);
		p_px[1] = pos[1] + (dist[1] * dda->raydir[1]);
		px_put(game->data, p_px[0], p_px[1], ray->color);
		if (dist[0] < dist[1] && (dda->raydir[0] != 0))
			dist[0] += dda->d_dist[0];
		else
			dist[1] += dda->d_dist[1];
	}
	if (dda->raydir[ray->side] > 0)
		px_put(game->data, p_px[0] + 1, p_px[1] + 1, ray->color);
}

unsigned int	convert_int(int rgb[3])
{
	unsigned int	res;

	res = 0;
	res = (rgb[0]);
	res = (res << 8) + rgb[1];
	res = (res << 8) + rgb[2];
	return (res);
}
