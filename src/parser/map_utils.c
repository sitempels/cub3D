/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:37:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/26 12:54:39 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_game(t_game *game, int rows)
{
	if (game->config->player_count == 0)
		return (ft_error(NO_PLAYER, NULL), 1);
	game->map = malloc(sizeof(int *) * (rows));
	if (!game->map)
		return (1);
	game->screen_width = WIDTH;
	game->screen_height = HEIGHT;
	game->fov = FOV;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (1);
	ft_memset(game->player, 0, sizeof(t_player));
	return (0);
}

static void	init_player(t_game *game, int y, int x, double facing)
{
	game->player->facing = facing;
	game->player->pos[0] = (x + 0.5);
	game->player->pos[1] = (y + 0.5);
	game->map[y][x] = FLOOR;
}

static void	pad_map_row(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < game->max_x)
	{
		game->map[y][x] = -1;
		x++;
	}
}

int	init_map(t_game *game, char *line, int curr_row, int line_lenght)
{
	int	j;

	pad_map_row(game, curr_row);
	j = 0;
	while (j < line_lenght)
	{
		if (line[j] == ' ' || line[j] == '\n' || line[j] == '\t')
			game->map[curr_row][j] = EMPTY;
		else if (line[j] == '0')
			game->map[curr_row][j] = FLOOR;
		else if (line[j] == '1')
			game->map[curr_row][j] = WALL;
		else if (line[j] == 'N')
			init_player(game, curr_row, j, NORTH);
		else if (line[j] == 'S')
			init_player(game, curr_row, j, SOUTH);
		else if (line[j] == 'E')
			init_player(game, curr_row, j, EAST);
		else if (line[j] == 'W')
			init_player(game, curr_row, j, WEST);
		else
			return (1);
		j++;
	}
	return (0);
}
