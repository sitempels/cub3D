/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:51:51 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 16:52:42 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	**copy_map(int **map, t_game *game)
{
	int		**copy;
	int		y;
	int		x;

	copy = malloc(sizeof(int *) * (game->max_y + 2));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < game->max_y + 2)
	{
		copy[y] = malloc(sizeof(int) * (game->max_x + 2));
		if (!copy[y])
			return (NULL);
		x = 0;
		while (x < game->max_x + 2)
		{
			if (x == 0 || x == game->max_x + 1 || y == 0 || y == game->max_y + 1)
				copy[y][x] = -1;
			else
				copy[y][x] = map[y - 1][x - 1];
			x++;
		}
		y++;
	}
	return (copy);
}

int	check_map_closure(t_game *game)
{
	int	**copy;

	copy = game->map;
	game->map = copy_map(copy, game);
	if (!game->map)
		return (1);
	if (floodfill(0, 0, game, 'E') != 0)
		return (ft_error(UNCLOSED_MAP, NULL), 1);
	if (floodfill((int)(game->player->pos[1] - 0.5)
		, (int)(game->player->pos[0] - 0.5), game, 'I') != 0)
		return (ft_error(UNCLOSED_MAP, NULL), 1);
	print_map(game->map, game->max_y + 2, game->max_x + 2); // SUPPRIMER PRINT
	free_map(game->map, game->max_y + 2);
	game->map = copy;
	print_map(game->map, game->max_y, game->max_x); // SUPPRIMER PRINT
	return (0);
}

int	floodfill(t_game *game, int y, int x, char flag)
{
	int	**map;

	map = game->map;
	if (flag == 'I')
	{
		if (x < 0 || y < 0 || x >= game->max_x + 2 || y >= game->max_x + 2)
			return (1);
		else if (map[y][x] == WALL || map[y][x] == FILLED)
			return (0);
	}
	else if (flag == 'E')
	{
		if ((x < 0 || y < 0 || x >= game->max_x + 2 || y >= game->max_y + 2)
			|| (map[y][x] == WALL || map[y][x] == FILLED))
			return (0);
		if (map[y][x] == FLOOR)
			return (1);
	}
	map[y][x] = FILLED;
	return (floodfill(game, y, x + 1, flag)
		|| floodfill(game, y, x -1, flag)
		|| floodfill(game, y + 1, x, flag)
		|| floodfill(game, y - 1, x, flag));
}
