/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:05:50 by stempels          #+#    #+#             */
/*   Updated: 2025/09/24 16:05:31 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		dda_init(t_game *game, t_dda *dda, t_ray *ray);
static void		get_first_dist(t_game *game, t_dda *dda, t_ray *ray);
static void		collision_dist(t_game *game, t_dda *dda, t_ray *ray);

void	dda_operation(t_game *game, float facing)
{
	float	camera;
	float	plane[2];
	t_dda	dda;
	t_ray	ray;

	dda.dir[0] = get_angle(0, facing);
	dda.dir[1] = get_angle(1, facing);
	plane[0] = -tan(game->fov * M_PI / 360) * get_angle(1, facing);
	plane[1] = tan(game->fov * M_PI / 360) * get_angle(0, facing);
	ray.color = RAY_COLOR;
	ray.x = 0;
	while (ray.x < game->screen_width)
	{
		camera = (2 * ray.x / (float)game->screen_width) - 1;
		dda.raydir[0] = dda.dir[0] + plane[0] * camera;
		dda.raydir[1] = dda.dir[1] + plane[1] * camera;
		dda_init(game, &dda, &ray);
		if (game->minimap && game->show_fov)
			draw_line(game, &dda, &ray);
		draw_wall(game, &dda, &ray);
		ray.x++;
	}
	return ;
}

void	dda_collision(t_game *game, float move[2], float camera)
{
	float	test;
	t_dda	dda;
	t_ray	ray;

	safe_angle_add(&camera, -90);
	ray.color = 0x0f66ffff;
	ray.x = -90;
	while (ray.x <= 90)
	{
		dda.raydir[0] = get_angle(0, camera);
		dda.raydir[1] = get_angle(1, camera);
		dda_init(game, &dda, &ray);
		test = (ray.dist - COLL_DIST);
		if (test <= move[ray.side] * dda.step[ray.side])
			move[ray.side] = test * dda.step[ray.side];
		if (game->minimap && game->show_col)
			draw_line(game, &dda, &ray);
		ray.x++;
		safe_angle_add(&camera, 1);
	}
	return ;
}

static void	dda_init(t_game *game, t_dda *dda, t_ray *ray)
{
	dda->map[0] = (int)game->player->pos[0];
	dda->map[1] = (int)game->player->pos[1];
	if (dda->raydir[0] == 0)
		dda->d_dist[0] = 900000000;
	else
		dda->d_dist[0] = fabs(1 / dda->raydir[0]);
	if (dda->raydir[1] == 0)
		dda->d_dist[1] = 900000000;
	else
		dda->d_dist[1] = fabs(1 / dda->raydir[1]);
	get_first_dist(game, dda, ray);
	return ;
}

static void	get_first_dist(t_game *game, t_dda *dda, t_ray *ray)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (dda->raydir[i] < 0)
		{
			dda->step[i] = -1;
			dda->side_dist[i] = (game->player->pos[i] - dda->map[i]);
		}
		else
		{
			dda->step[i] = 1;
			dda->side_dist[i] = (dda->map[i] + 1.0 - game->player->pos[i]);
		}
		dda->side_dist[i] *= dda->d_dist[i];
		i++;
	}
	collision_dist(game, dda, ray);
	return ;
}

static void	collision_dist(t_game *game, t_dda *dda, t_ray *ray)
{
	int		i;

	while (1)
	{
		if (dda->side_dist[0] < dda->side_dist[1])
			i = 0;
		else
			i = 1;
		dda->side_dist[i] += dda->d_dist[i];
		dda->map[i] += dda->step[i];
		ray->side = i;
		if (game->map[dda->map[1]][dda->map[0]] == 1)
			break ;
	}
	ray->dist = dda->side_dist[i] - dda->d_dist[i];
	return ;
}
