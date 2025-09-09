/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/09 15:25:55 by stempels         ###   ########.fr       */
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
	if (key_code == UP_KEY)
	{
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		player->pos_x = player->pos_x + sinf(player->facing) * SPEED_FORWARD;
		player->pos_y = player->pos_y + cosf(player->facing) * SPEED_FORWARD;
		printf("forward %d\n", SPEED_FORWARD);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		game_loop(game, data);
	}
	else if (key_code == DOWN_KEY)
	{
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		player->pos_x = player->pos_x - sinf(player->facing) * SPEED_BACKWARD;
		player->pos_y = player->pos_y - cosf(player->facing) * SPEED_BACKWARD;
		printf("backward %d\n", SPEED_BACKWARD);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		game_loop(game, data);
	}
	else if (key_code == LEFT_KEY)
	{
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		player->facing += TURN_SPEED; 
		if (player->facing >= 2 * M_PI)
			player->facing -= 2 * M_PI;
		printf("backward %d\n", SPEED_BACKWARD);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		game_loop(game, data);
	}
	else if (key_code == RIGHT_KEY)
	{
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		player->facing -= TURN_SPEED;
		if (player->facing < 0)
			player->facing += 2 * M_PI;
		printf("turn right %f\n", TURN_SPEED);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
		game_loop(game, data);
	}
	return (0);
}
