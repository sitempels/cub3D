/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:10:39 by stempels          #+#    #+#             */
/*   Updated: 2025/09/26 17:05:46 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_line(t_game *game, t_dda *dda, t_ray *ray)
{
	float	pos[2];
	float	p_px[2];
	float	dist[2];

	pos[0] = game->player->pos[0] * game->mini_size + MINI_BORDER_L / 2;
	pos[1] = game->player->pos[1] * game->mini_size + MINI_BORDER_L / 2 - 1;
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
		px_put(game->data, p_px[0] - (1 + 1 * dda->step[0]),
			p_px[1], ray->color);
}

void	draw_player(t_game *game, t_data *data, unsigned int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = game->player->pos[0] * game->mini_size + MINI_BORDER_L / 2 - 1;
	y = game->player->pos[1] * game->mini_size + MINI_BORDER_L / 2 - 1;
	x = x - game->mini_size / 4;
	y = y - game->mini_size / 4;
	i = 0;
	while (i < game->mini_size / 2)
	{
		j = 0;
		while (j < game->mini_size / 2)
		{
			px_put(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
	return ;
}

void	draw_minimap(t_game *game, t_data *data)
{
	int	i[4];

	i[2] = MINI_BORDER_L / 2 - 1;
	i[3] = MINI_BORDER_L / 2 - 1;
	i[1] = -1;
	while (++i[1] < game->mini_height + MINI_BORDER_L)
	{
		i[0] = -1;
		while (++i[0] < game->mini_width + MINI_BORDER_L)
			px_put(data, i[0], i[1], MINI_BORDER_COLOR);
	}
	i[1] = -1;
	while (++i[1] < game->max_y)
	{
		i[0] = -1;
		while (++i[0] < game->max_x)
		{
			if (game->map[i[1]][i[0]] == FLOOR)
				block_put(data, i, game->mini_size, FLOOR_COLOR);
			else if (game->map[i[1]][i[0]] == WALL)
				block_put(data, i, game->mini_size, WALL_COLOR);
			else if (game->map[i[1]][i[0]] == EMPTY)
				block_put(data, i, game->mini_size, MINI_BACKGROUND);
		}
	}
}

void	block_put(t_data *data, int coord[4], int size_mod, unsigned int color)
{
	int	i;
	int	j;

	i = size_mod;
	while (i >= 0)
	{
		j = size_mod;
		while (j > 0)
		{
			px_put(data, (coord[0]) * size_mod + j + coord[2],
				(coord[1]) * size_mod + i + coord[3], color);
			j--;
		}
		i--;
	}
}

void	px_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return ;
	dst = data->addr + (y * data->l_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
