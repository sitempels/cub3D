/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/25 12:11:29 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_handler(t_game *game, int keycode);
static void	toggle_handler(t_game *game, int keycode);

int	key_handler(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		return (1);
	else if (keycode == W_KEY || keycode == S_KEY
			|| keycode == A_KEY || keycode == D_KEY
			|| keycode == LEFT_KEY || keycode == RIGHT_KEY)
		move_handler(game, keycode);
	else if (keycode == COMMA_KEY || (F_KEY <= keycode && keycode <= H_KEY))
		toggle_handler(game, keycode);
	return (0);
}

static void	move_handler(t_game *game, int keycode)
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

static void	toggle_handler(t_game *game, int keycode)
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

float	safe_angle_add(float *angle, float mod)
{
	*angle += mod;
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
	return (*angle);
}
