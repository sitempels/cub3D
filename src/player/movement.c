/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:58:33 by stempels          #+#    #+#             */
/*   Updated: 2025/09/24 15:59:20 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	move_player(t_game *game, t_data *data, int camera)
{
	float		move[2];
	t_player	*player;

	player = game->player;
	if (game->minimap == 1)
		draw_minimap(game, data);
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

int	turn_player(t_game *game, t_data *data, int key_code)
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
