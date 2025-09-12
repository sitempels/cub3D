/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/11 16:34:16 by stempels         ###   ########.fr       */
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
	if (LEFT_KEY <= keycode && keycode <= DOWN_KEY )
		return (move_player(game, game->data, keycode));
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
		speed = SPEED * SPEED_RATIO * (0xff53 - key_code);
		player->pos[0] = player->pos[0] + cosf(player->facing) * speed;
		player->pos[1] = player->pos[1] + sinf(player->facing) * speed;
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		game_loop(game);
	}
	else if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
	{
		double	turn;
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		turn = TURN_SPEED * (0xff52 - key_code );
		safe_angle_add(&player->facing, turn);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		game_loop(game);
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
	while (i < game->max_y)
	{
		j = 0;
		while (j < game->max_x)
		{
			if (game->map[i][j] == FLOOR)
				img_put(data, j, i, FLOOR_COLOR);
			if (game->map[i][j] == WALL)
				img_put(data, j, i, WALL_COLOR);
			j++;
		}
		i++;
	}
	return ;
}
