/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/19 16:29:47 by stempels         ###   ########.fr       */
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
	if (keycode == 0x2c)
		game->minimap = (game->minimap + 1) % 2;
	if (keycode == 0x66)
		game->fov_show = (game->fov_show + 1) % 2;
	return (0);
}

static int	move_player(t_game *game, t_data *data, int key_code)
{
	t_player	*player;

	player = game->player;
	if (key_code == UP_KEY || key_code == DOWN_KEY)
	{
		int		sens;
		double	move[2];
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		if (game->minimap)
			draw_player(game, data, FLOOR_COLOR);
		sens = 0xff53 - key_code;
		move[0] = get_angle(0, player->facing) * SPEED * sens;
		move[1] = get_angle(1, player->facing) * SPEED * sens;
		dda_collision(game, move);
		game->player->pos[0] += move[0];
		game->player->pos[1] += move[1];
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		game_loop(game);
	}
	else if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
	{
		double	turn;
		printf("player before	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		turn = TURN_SPEED * (key_code - 0xff52);
		safe_angle_add(&player->facing, turn);
		printf("player after	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
		game_loop(game);
	}
	return (0);
}

void	safe_angle_add(float *angle, float mod)
{
	*angle += mod;
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
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
				img_put(data, i, MINI_SIZE, FLOOR_COLOR);
			if (game->map[i[1]][i[0]] == WALL)
				img_put(data, i, MINI_SIZE, WALL_COLOR);
			i[0]++;
		}
		i[1]++;
	}
	draw_player(game, data, PLAYER_COLOR);
	return ;
}
