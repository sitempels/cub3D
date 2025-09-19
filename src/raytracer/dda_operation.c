/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:05:50 by stempels          #+#    #+#             */
/*   Updated: 2025/09/19 16:38:19 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static float	dda_init(t_game *game, t_dda *dda, t_ray *ray);
static float	get_first_dist(t_game *game, t_dda *dda, t_ray *ray);
static float	collision_dist(t_game *game, t_dda *dda, t_ray *ray);
static void		draw_line(t_game *game, t_dda *dda, t_ray *ray);
static void		draw_wall(t_game *game, t_dda *dda, t_ray *ray, int x);

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

float	dda_operation(t_game *game, float facing)
 {
	int		x;
	float	camera_x;
	float	plane[2];
	t_dda	dda;
	t_ray	ray;

	dda.limit = 500;
	dda.dir[0] = get_angle(0, facing);
	dda.dir[1] = get_angle(1, facing);
	plane[0] = - tan(game->fov * M_PI / 360) * get_angle(1, facing);
	plane[1] = tan(game->fov * M_PI / 360) * get_angle(0, facing);
	ray.color = RAY_COLOR;
	x = 0;
	while (x <= game->screen_width)
 	{
		camera_x = (2 * x / (float)game->screen_width) - 1;
		dda.raydir[0] = dda.dir[0] + plane[0] * camera_x;
		dda.raydir[1] = dda.dir[1] + plane[1] * camera_x;
		dda_init(game, &dda, &ray);
		if (game->minimap && game->fov_show)
			draw_line(game, &dda, &ray);
		draw_wall(game, &dda, &ray, x);
		x++;
	}
	return (0);
}

static void	draw_wall(t_game *game, t_dda *dda, t_ray *ray, int x)
{
	int	wall_height;
	int	wall_down;
	int	wall_up;
	int	i;
	unsigned int	color;

	wall_height = (int)(game->screen_height / ray->dist);
	wall_down = -wall_height / 2 + game->screen_height / 2;
	if (wall_down < 0)
		wall_down = 0;
	wall_up = wall_height / 2 + game->screen_height / 2;
	if (wall_up < 0)
		wall_up = game->screen_height - 1;
	if (ray->side == 0 )
	{
		color = 0xff000066;
		if (dda->raydir[ray->side] < 0)
			color = 0xff000045;
	}
	if (ray->side == 1 )
	{
		color = 0xff006600;
		if (dda->raydir[ray->side] < 0)
			color = 0xff004500;
	}
	i = wall_down;
	while (i <= wall_up)
	{
		if (game->minimap)
		{
			if (x < game->mini_width)
				if (i < game->mini_height)
					i = game->mini_height + 4;
		}
		px_put(game->data, x, i, color);
		i++;
	}
	return ;
}

void	refresh_screen(t_game *game)
{
	int	i;
	int	j;
	unsigned int	color;

	i = 0;
	while (i <= game->screen_width)
	{
		j = 0;
		while (j <= game->screen_height)
		{
			if (j < game->screen_height / 2)
				color = SKY_COLOR;
			if (j >= game->screen_height / 2)
				color = SOIL_COLOR;
			px_put(game->data, i, j, color);
			j++;
		}
		i++;
	}
	return ;
}

float	dda_collision(t_game *game, double move[2])
{
	float	x;
	t_dda	dda;
	t_ray	ray;

	dda.limit = COLL_DIST;
	ray.color = 0x0f66ffff;
	x = game->player->facing;
	while (1)
	{
		dda.raydir[0] = get_angle(0, x);
		dda.raydir[1] = get_angle(1, x);
		dda_init(game, &dda, &ray);
		if (ray.dist <= dda.limit)
		{
			printf("move value pre	x: %f	y: %f\n", move[0], move[1]);
		//	move[ray.side] += -dda.raydir[ray.side] * (2 * COLL_DIST - ray.dist);
		//	move[1] += COLL_DIST - (-dda.raydir[1] * ray.dist);
			printf("move value	x: %f	y: %f\nraydir value	x: %f	y: %f\nraydist: %f\n", move[0], move[1], dda.raydir[0], dda.raydir[1], ray.dist);
			draw_line(game, &dda, &ray);
		}
//		else if (ray.dist > dda.limit && ray.dist == dda.d_dist[ray.side])
//			game->player->pos[ray.side] += -dda.raydir[ray.side] * (ray.dist - COLL_DIST);
		safe_angle_add(&x, 1);
		if (x == game->player->facing)
			break ;
	}
	return (0);
}

static float	dda_init(t_game *game, t_dda *dda, t_ray *ray)
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
	return (0);
}

static float	get_first_dist(t_game *game, t_dda * dda, t_ray *ray)
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
//			dda->side_dist[i] = (game->player->pos[i] - dda->map[i]) * dda->d_dist[i];
		}
		i++;
	}
	return (collision_dist(game, dda, ray));
}

static float	collision_dist(t_game *game, t_dda *dda, t_ray *ray)
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
	return (0);
}

static void	draw_line(t_game *game, t_dda *dda, t_ray *ray)
{
	float	x;
	float	y;
	float	dist_x;
	float	dist_y;

	x = game->player->pos[0] * MINI_SIZE;
	y = game->player->pos[1] * MINI_SIZE;
	dist_x = 0;
	dist_y = 0;
	while ((ray->side == 0 && dist_x < ray->dist * MINI_SIZE)
		|| (ray->side == 1 && dist_y < ray->dist * MINI_SIZE))
	{
		px_put(game->data, x + (dist_x * dda->raydir[0]), y + (dist_y * dda->raydir[1]), ray->color);
		if (dist_x < dist_y && (dda->raydir[0] != 0))
			dist_x += dda->d_dist[0];
		else
			dist_y += dda->d_dist[1];
	}
}
