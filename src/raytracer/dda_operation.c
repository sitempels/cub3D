/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:24:02 by stempels          #+#    #+#             */
/*   Updated: 2025/09/16 17:18:28 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	dda_init(t_game *game, t_dda *dda, t_ray *ray);
static double	get_first_dist(t_game *game, t_dda *dda, t_ray *ray);
static double	collision_dist(t_game *game, t_dda *dda, t_ray *ray);
static void		draw_line(t_game *game, t_dda *dda, t_ray *ray);
//static double	collision_detector(t_game *game, t_dda *dda, t_ray * ray);

double	dda_operation(t_game *game, double facing)
{
	int		x;
	t_dda	dda;
	t_ray	ray;

	dda.dir[0] = cosf(facing);
	dda.dir[1] = sinf(facing);
	dda.plane[0] = - tan(game->fov * M_PI / 360) * sinf(facing);
	dda.plane[1] = tan(game->fov * M_PI / 360) * cosf(facing);
	dda.limit = 9999;

	ray.color = RAY_COLOR;
	x = 0;
	while (x <= game->screen_width)
	{
		dda.camera_x = (2 * x / (double)game->screen_width) - 1;
		dda_init(game, &dda, &ray);
		draw_line(game, &dda, &ray);
		x++;
	}
	return (0);
}

static double	dda_init(t_game *game, t_dda *dda, t_ray *ray)
{
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
	get_first_dist(game, dda, ray);
	return (0);
}
/*
static double	collision_detector(t_game *game, t_dda *dda)
{
	double	x;
	double	wall_dist;

	x = 0;
	dda.limit = 1;	
	dda.plane[0] = - plane_y_size * sinf(game->player->facing);
	dda.plane[1] = plane_y_size * cosf(game->player->facing);
	while (x < 2 * M_PI)
	{
		dda->camera_x = (2 * x / (double)game->screen_width) - 1;
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
}
*/
static double	get_first_dist(t_game *game, t_dda * dda, t_ray *ray)
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
	return (collision_dist(game, dda, ray));
}

static double	collision_dist(t_game *game, t_dda *dda, t_ray *ray)
{
	int		i;
	int		hit;

	hit = 0;
	while (hit == 0 && (ft_abs(ray->dist) < dda->limit))
	{
		if (dda->side_dist[0] < dda->side_dist[1])
			i = 0;
		else
			i = 1;
		dda->side_dist[i] += dda->d_dist[i];
		dda->map[i] += dda->step[i];
		ray->side = i;
		if (game->map[dda->map[1]][dda->map[0]] > 0)
			hit = 1;
		ray->dist = dda->side_dist[i] - dda->d_dist[i];
	}
	return (0);
}

static void	draw_line(t_game *game, t_dda *dda, t_ray *ray)
{
	double	x;
	double	y;
	double	dist_x;
	double	dist_y;

	x = game->player->pos[0] * SIZE_MOD;
	y = game->player->pos[1] * SIZE_MOD;
	dist_x = 0;
	dist_y = 0;
	while ((ray->side == 0 && dist_x < ray->dist * SIZE_MOD)
		|| (ray->side == 1 && dist_y < ray->dist * SIZE_MOD))
	{
		px_put(game->data, x + (dist_x * dda->raydir[0]), y + (dist_y * dda->raydir[1]), ray->color);
		if (dist_x < dist_y && (dda->raydir[0] != 0))
			dist_x += dda->d_dist[0];
		else
			dist_y += dda->d_dist[1];
	}
}
