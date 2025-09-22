#include "cub3D.h"

int	**copy_map(t_game *game)
{
	int **copy;
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
			if (x == 0 || x == game->max_x + 1 || y == 0 || y == game->max_y + 1 )
				copy[y][x] = -1;
			else
				copy[y][x] = game->map[y - 1][x - 1];
			x++;
		}
		y++;
	}
	return (copy);
}

int	check_map_closure(t_game *game)
{
	int **copy;

	copy = copy_map(game);
	if (!copy)
		return (1);
	if (floodfill(copy, 0, 0, game, 'E') != 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error : Map is not closed\n");
		return (1);
	}
	if (floodfill(copy, (int) (game->player->pos[1] - 0.5), (int) (game->player->pos[0] - 0.5), game, 'I') != 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error : Map is not closed\n");
		return (1);
	}
	print_map(copy, game->max_y + 2, game->max_x + 2); // SUPPRIMER PRINT
	free_map(copy, game->max_y + 2);
	return (0);
}

int	floodfill(int **map, int y, int x, t_game *game, char flag)
{
	if (flag == 'I')
	{
		if (x < 0 || y < 0 || x >= game->max_x + 2 || y >= game->max_x + 2 )
			return (1);
		else if (map[y][x] == WALL || map[y][x] == FILLED)
			return (0);
	}
	else if (flag == 'E')
	{
		if ((x < 0 || y < 0 || x >= game->max_x + 2 || y >= game->max_y + 2) || (map[y][x] == WALL || map[y][x] == FILLED))
			return (0);
		if (map[y][x] == FLOOR)
			return (1);
	}
	map[y][x] = FILLED;
	return (floodfill(map, y, x + 1, game, flag) || floodfill(map, y, x -1, game, flag)
	|| floodfill(map, y + 1, x, game, flag) ||floodfill(map, y - 1, x, game, flag));
}
