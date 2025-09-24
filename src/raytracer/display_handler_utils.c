/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/24 18:56:22 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_handler(int keycode, t_game *game)
{
	float	camera;

	camera = game->player->facing;
	if (keycode == ESC_KEY)
		return (1);
	if (keycode == W_KEY)
		return (move_player(game, game->data, camera));
	if (keycode == S_KEY)
		return (move_player(game, game->data, safe_angle_add(&camera, 180)));
	if (keycode == A_KEY)
		return (move_player(game, game->data, safe_angle_add(&camera, -90)));
	if (keycode == D_KEY)
		return (move_player(game, game->data, safe_angle_add(&camera, 90)));
	if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		return (turn_player(game, game->data, keycode));
	if (keycode == 0x2c)
		game->minimap = (game->minimap + 1) % 2;
	if (keycode == 0x66)
		game->show_fps = (game->show_fps + 1) % 2;
	if (keycode == 0x67)
		game->show_fov = (game->show_fov + 1) % 2;
	if (keycode == 0x68)
		game->show_col = (game->show_col + 1) % 2;
	return (0);
}

float	safe_angle_add(float *angle, float mod)
{
	*angle += mod;
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
	return (*angle);
}

void	draw_player(t_game *game, t_data *data, unsigned int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = game->player->pos[0] * MINI_SIZE;
	y = game->player->pos[1] * MINI_SIZE;
	x = x - MINI_SIZE / 4;
	y = y - MINI_SIZE / 4;
	i = 0;
	while (i < MINI_SIZE / 2)
	{
		j = 0;
		while (j < MINI_SIZE / 2)
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
	int	i[2];

	i[1] = 0;
	while (i[1] < game->max_y)
	{
		i[0] = 0;
		while (i[0] < game->max_x)
		{
			if (game->map[i[1]][i[0]] == FLOOR)
				img_put(data, i, game->mini_size, FLOOR_COLOR);
			else if (game->map[i[1]][i[0]] == WALL)
				img_put(data, i, game->mini_size, WALL_COLOR);
			else
				img_put(data, i, game->mini_size, MINI_BACKGROUND);
			i[0]++;
		}
		i[1]++;
	}
	i[0] = -1;
	while (++i[0] < game->max_x)
		img_put(data, i, game->mini_size, MINI_BACKGROUND);
	return ;
}

