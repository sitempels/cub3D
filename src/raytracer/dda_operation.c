/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:24:02 by stempels          #+#    #+#             */
/*   Updated: 2025/09/11 17:55:04 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	dda_init(t_game *game, t_dda *dda, int *side);
static double	get_first_dist(t_game *game, t_dda *dda, int *side);
static double	collision_dist(t_game *game, t_dda *dda, int *side);
static void	draw_line(t_game *game, t_dda *dda, double dist, int side);

double	dda_operation(t_game *game, double facing)
{
	int		side;
	double	wall_dist;
	double	old_plane_x;
	double	plane_y_size;
	t_dda	dda;
//	double	time;
//	double	old_time;

	if (0 < facing && facing < M_PI)
		dda.dir[0] = -1;
	else if (facing == 0 || facing == M_PI)
		dda.dir[0] = 0;
	else
		dda.dir[0] = 1;
	if (M_PI / 2 < facing && facing < 3 * M_PI / 2)
		dda.dir[1] = -1;
	else if (facing == M_PI / 2 || facing == 3 * M_PI / 2)
		dda.dir[1] = 0;
	else
		dda.dir[1] = 1;

//	plane_x_size = 0;
//	plane_y_size = (game->fov * 180) / (M_PI * 100);
	dda.plane[0] = -0.66 * sinf(facing);
	dda.plane[1] = 0.66 * cosf(facing);
	//dda.plane[0] = 0;
	//dda.plane[1] = 0.66;
	//time = 0;
	//old_time = 0;
	wall_dist = dda_init(game, &dda, &side);
	return (0);
}

static double	dda_init(t_game *game, t_dda *dda, int *side)
{
	int		x;
	double	wall_dist;

	x = 0;
	while (x < (game->max_x * SIZE_MOD))
	{
		dda->camera_x = (2 * x) / (((double)game->max_x * SIZE_MOD) - 1);
		dda->raydir[0] = dda->dir[0] + dda->plane[0] * dda->camera_x;
		dda->raydir[1] = dda->dir[1] + dda->plane[1] * dda->camera_x;
		dda->map[0] = (int)game->player->pos[0];
		if (dda->raydir[0] == 0)
			dda->d_dist[0] = 2000;
		else
			dda->d_dist[0] = fabs(1 / dda->raydir[0]);
		dda->map[1] = (int)game->player->pos[1];
		if (dda->raydir[1] == 0)
			dda->d_dist[1] = 2000;
		else
			dda->d_dist[1] = fabs(1 / dda->raydir[1]);
		wall_dist = get_first_dist(game, dda, side);
		draw_line(game, dda, wall_dist, *side);
		x++;
	}
	return (wall_dist);
}

static double	get_first_dist(t_game *game, t_dda * dda, int *side)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (dda->raydir[i] < 0)
		{
			dda->step[i] = -1;
			dda->side_dist[i] = (game->player->pos[i] - dda->map[i]) * dda->d_dist[i];
		}
		else
		{
			dda->step[i] = 1;
			dda->side_dist[i] = (dda->map[i] + 1.0 - game->player->pos[i]) * dda->d_dist[i];
		}
		i++;
	}
	return (collision_dist(game, dda, side));
}

static double	collision_dist(t_game *game, t_dda *dda, int *side)
{
	int		i;
	int		hit;

	hit = 0;
	while (hit == 0 && (game->max_x > dda->map[0] && game->max_y > dda->map[1]))
	{
		if (dda->side_dist[0] < dda->side_dist[1])
			i = 0;
		else
			i = 1;
		dda->side_dist[i] += dda->d_dist[i];
		dda->map[i] -= dda->step[i];
		*side = i;
		if (game->map[dda->map[1]][dda->map[0]] > 0)
			hit = 1;
	}
	return (dda->side_dist[i] - dda->d_dist[i]);
}

static void	draw_line(t_game *game, t_dda *dda, double dist, int side)
{
	int	x;
	int	y;
	double	dist_x;
	double	dist_y;

	x = game->player->pos[0] * SIZE_MOD;
	y = game->player->pos[1] * SIZE_MOD;
	dist_x = 0;
	dist_y = 0;
	while ((side == 0 && dist_x < dist * SIZE_MOD) || (side == 1 && dist_y < dist * SIZE_MOD))
	{
		px_put(game->data, x - (dist_x * dda->step[0]), y - (dist_y * dda->step[1]), 0x74a33e);
		if (dda->raydir[0] != 0 && (dist_x < dist_y || dda->raydir[1] == 0))
			dist_x += dda->d_dist[0];
		else
			dist_y += dda->d_dist[1];
	}
	mlx_put_image_to_window(game->data->mlx, game->data->win, game->data->img, 0, 0);
}
