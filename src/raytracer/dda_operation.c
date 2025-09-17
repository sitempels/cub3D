/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:24:02 by stempels          #+#    #+#             */
/*   Updated: 2025/09/17 16:23:30 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	dda_init(t_game *game, t_dda *dda, t_ray *ray);
static double	get_first_dist(t_game *game, t_dda *dda, t_ray *ray);
static double	collision_dist(t_game *game, t_dda *dda, t_ray *ray);
static void		draw_line(t_game *game, t_dda *dda, t_ray *ray);

double	dda_operation(t_game *game, double facing)
{
	int		x;
	double	camera_x;
	double	plane[2];
	t_dda	dda;
	t_ray	ray;

	dda.limit = 9999;
	dda.dir[0] = cosf(facing);
	dda.dir[1] = sinf(facing);
	plane[0] = - tan(game->fov * M_PI / 360) * sinf(facing);
	plane[1] = tan(game->fov * M_PI / 360) * cosf(facing);
	ray.color = RAY_COLOR;
	x = 0;
	while (x <= game->screen_width)
	{
		camera_x = (2 * x / (double)game->screen_width) - 1;
		dda.raydir[0] = dda.dir[0] + plane[0] * camera_x;
		dda.raydir[1] = dda.dir[1] + plane[1] * camera_x;
		dda_init(game, &dda, &ray);
		draw_line(game, &dda, &ray);
		x++;
	}
	return (0);
}

double	dda_collision(t_game *game)
{
	double		x;
	t_dda	dda;
	t_ray	ray;

	dda.limit = COLL_DIST;
	ray.color = 0x66ffff;
	x = 0;
	while (x <= 2 * M_PI)
	{
		dda.raydir[0] = cosf(x);
		dda.raydir[1] = sinf(x);
		dda_init(game, &dda, &ray);
		if (ray.dist > 0)
			game->player->pos[ray.side] += -dda.raydir[ray.side] * (COLL_DIST - ray.dist);
		draw_line(game, &dda, &ray);
		x += 0.01;
	}
	return (0);
}

static double	dda_init(t_game *game, t_dda *dda, t_ray *ray)
{
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
	while (hit == 0)
	{
		if (dda->side_dist[0] < dda->side_dist[1])
			i = 0;
		else
			i = 1;
		dda->side_dist[i] += dda->d_dist[i];
		dda->map[i] += dda->step[i];
		ray->side = i;
		if (game->map[dda->map[1]][dda->map[0]] > 0)
		{
			hit = 1;
			ray->dist = dda->side_dist[i] - dda->d_dist[i];
			if (ray->dist > dda->limit)
				ray->dist = 0;
		}
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
