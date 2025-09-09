/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:24:02 by stempels          #+#    #+#             */
/*   Updated: 2025/09/09 20:17:08 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	dda_init(t_game *game, double dir[2], double plane[2], int *side);
static double	get_first_dist(t_game *game, double raydir[2], int map[2], int *side);
static double	collision_dist(t_game *game, double d_dist[2], double side_dist[2], int *side, int step[2], int map[2]);
static void	draw_line(t_game *game, double dist, double facing);

double	dda_operation(t_game *game, double facing)
{
	int		side;
	double	dir[2];
	double	plane[2];
	double	wall_dist;
//	double	time;
//	double	old_time;

	if (0 < facing && facing < M_PI)
		dir[0] = 1;
	else if (facing == 0 || facing == M_PI)
		dir[0] = 0;
	else
		dir[0] = -1;
	if (-M_PI / 2 < facing && facing < M_PI / 2)
		dir[1] = 1;
	else if (facing == -M_PI / 2 || facing == M_PI / 2)
		dir[1] = 0;
	else
		dir[1] = -1;

	plane[0] = 0;
	plane[1] = game->fov / 100;
	//time = 0;
	//old_time = 0;
	wall_dist = dda_init(game, dir, plane, &side);
	draw_line(game, wall_dist, facing);
	return (0);
}
static double	dda_init(t_game *game, double dir[2], double plane[2], int *side)
{
	int		x;
	int		map[2];
	double	raydir[2];
	double	camera_x;

	x = 0;
	while (x < game->max_x)
	{
		camera_x = 2 * x / (double)game->max_x - 1;
		raydir[0] = dir[0] + plane[0] * camera_x;
		raydir[1] = dir[1] + plane[1] * camera_x;
		x++;
	}
	x = 0;
	while (x < 2)
	{
		map[x] = (int)game->player->pos[x];
		if (raydir[x] == 0)
			raydir[x] = INT_MAX;
		else
			raydir[x] = fabs(1 / raydir[x]);
		x++;
	}
	return (get_first_dist(game, raydir, map, side));
}

static double	get_first_dist(t_game *game, double raydir[2], int map[2], int *side)
{
	int		i;
	int		step[2];
	double	d_dist[2];
	double	side_dist[2];

	i = 0;
	while (i < 2)
	{
		if (raydir[i] < 0)
		{
			step[i] = -1;
			side_dist[i] = (game->player->pos[i] - map[i]) * d_dist[i];
		}
		else
		{
			step[i] = 1;
			side_dist[i] = (map[i] + 1.0 - game->player->pos[i]) * d_dist[i];
		}
		i++;
	}
	return (collision_dist(game, d_dist, side_dist, side, step, map));
}

static double	collision_dist(t_game *game, double d_dist[2], double side_dist[2], int *side, int step[2], int map[2])
{
	int		i;
	int		hit;

	hit = 0;
	i = 0;
	while (hit == 0 && (game->max_x < map[0] && game->max_y < map[1]))
	{
		if (side_dist[0] >= side_dist[1])
			i = 1;
		side_dist[i] += d_dist[i];
		map[i] += step[i];
		*side = i;
		if (game->map[map[0]][map[1]] > 0)
			hit = 1;
	}
	return (side_dist[i] - d_dist[i]);
}

static void	draw_line(t_game *game, double dist, double facing)
{
	int	x;
	int	y;
	float	dist_x;
	float	dist_y;

	dist_x = sinf(facing) * dist;
	dist_y = cosf(facing) * dist;
	x = game->player->pos[0];
	y = game->player->pos[1];
	while (x < dist_x || y < dist_y)
	{
		px_put(game->data, x, y, 0x74a33e);
		if (x < y && x < dist_x)
			x += dist_x / 100;
		else
			y += dist_y / 100;
	}
	mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0, 0);
}
