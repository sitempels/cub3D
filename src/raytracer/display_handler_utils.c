/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/11 11:50:56 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	move_player(t_game *game, t_data *data, int key_code);

int	close_all(t_game *game, t_data *data, int status)
{
	if (!game && !data)
		exit(status);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(status);
}

int	key_handler(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		return (close_all(game, game->data, 0));
	if (keycode == UP_KEY)
		return (move_player(game, game->data, UP_KEY));
	if (keycode == DOWN_KEY)
		return (move_player(game, game->data, DOWN_KEY));
	if (keycode == LEFT_KEY)
		return (move_player(game, game->data, LEFT_KEY));
	if (keycode == RIGHT_KEY)
		return (move_player(game, game->data, RIGHT_KEY));
	return (0);
}

static int	move_player(t_game *game, t_data *data, int key_code)
{
	t_player	*player;

	player = game->player;
	if (key_code == UP_KEY || key_code == DOWN_KEY)
	{
		int	speed;
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		draw_player(game, data, FLOOR_COLOR);
		speed = (SPEED * SPEED_RATIO * (key_code - 0xff53));
		player->pos[0] = player->pos[0] + sinf(player->facing) * speed;
		player->pos[1] = player->pos[1] + cosf(player->facing) * speed;
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		game_loop(game, data);
	}
	else if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
	{
		double	turn;
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		turn = TURN_SPEED * -1 * (key_code - 0xff52);
		safe_angle_add(&player->facing, turn);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		game_loop(game, data);
	}
	return (0);
}

void	safe_angle_add(double *angle, double mod)
{
	*angle += mod;
	if (*angle < 0)
		*angle += 2 * M_PI;
	else if (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

void	draw_player(t_game *game, t_data *data, unsigned int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (game->player->pos[0] * (SIZE_MOD));
	y = (game->player->pos[1] * (SIZE_MOD));
	x = x - SIZE_MOD / 4;
	y = y - SIZE_MOD / 4;
	i = 0;
	while (i < SIZE_MOD / 2)
	{
		j = 0;
		while (j < SIZE_MOD / 2)
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
	int	i;
	int	j;

	i = 0;
	while (i < game->max_x)
	{
		j = 0;
		while (j < game->max_y)
		{
			if (game->map[i][j] == FLOOR)
				img_put(data, i, j, FLOOR_COLOR);
			if (game->map[i][j] == WALL)
				img_put(data, i, j, WALL_COLOR);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return ;
}
