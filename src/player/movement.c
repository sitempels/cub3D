/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:58:33 by stempels          #+#    #+#             */
/*   Updated: 2025/09/25 17:22:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	move_player(t_game *game, t_data *data, int camera);
static int	turn_player(t_game *game, t_data *data, int key_code);

void	move_handler(t_game *game, int keycode)
{
	float	camera;

	camera = game->player->facing;
	if (game->minimap == 1)
		draw_minimap(game, game->data);
	if (keycode == W_KEY)
		move_player(game, game->data, camera);
	else if (keycode == S_KEY)
		move_player(game, game->data, safe_angle_add(&camera, 180));
	else if (keycode == A_KEY)
		move_player(game, game->data, safe_angle_add(&camera, -90));
	else if (keycode == D_KEY)
		move_player(game, game->data, safe_angle_add(&camera, 90));
	else if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		turn_player(game, game->data, keycode);
}

static int	move_player(t_game *game, t_data *data, int camera)
{
	float		move[2];
	t_player	*player;

	player = game->player;
	printf("move\n");
	move[0] = get_angle(0, camera) * SPEED * game->frametime;
	move[1] = get_angle(1, camera) * SPEED * game->frametime;
	dda_collision(game, move, camera);
	game->player->pos[0] += move[0];
	game->player->pos[1] += move[1];
	if (game->minimap)
		draw_player(game, data, PLAYER_COLOR);
	game_loop(game);
	return (0);
}

static int	turn_player(t_game *game, t_data *data, int key_code)
{
	double		turn;
	t_player	*player;

	player = game->player;
	turn = TURN_SPEED * (key_code - 0xff52) * game->frametime;
	safe_angle_add(&player->facing, turn);
	if (game->minimap)
		draw_player(game, data, PLAYER_COLOR);
	game_loop(game);
	return (0);
}

void	toggle_handler(t_game *game, int keycode)
{
	if (keycode == 0x2c)
		game->minimap = (game->minimap + 1) % 2;
	if (keycode == 0x66)
		game->show_fps = (game->show_fps + 1) % 2;
	if (keycode == 0x67)
		game->show_fov = (game->show_fov + 1) % 2;
	if (keycode == 0x68)
		game->show_col = (game->show_col + 1) % 2;
	if (game->minimap)
	{
		draw_minimap(game, game->data);
		draw_player(game, game->data, PLAYER_COLOR);
	}
}
