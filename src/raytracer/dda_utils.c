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
	float	x;
	float	y;
	float	px;
	float	py;
	float	dist_x;
	float	dist_y;

	x = game->player->pos[0] * game->mini_size;
	y = game->player->pos[1] * game->mini_size;
	dist_x = 0;
	dist_y = 0;
	while ((ray->side == 0 && dist_x < ray->dist * game->mini_size)
		|| (ray->side == 1 && dist_y < ray->dist * game->mini_size))
	{
		px = x + (dist_x * dda->raydir[0]);
		py = y + (dist_y * dda->raydir[1]);
		px_put(game->data, px, py, ray->color);
		if (dist_x < dist_y && (dda->raydir[0] != 0))
			dist_x += dda->d_dist[0];
		else
			dist_y += dda->d_dist[1];
	}
	if (dda->raydir[ray->side] > 0) 
		px_put(game->data, px + 1, py + 1, ray->color);
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
