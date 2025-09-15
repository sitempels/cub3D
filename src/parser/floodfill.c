#include "cub3D.h"

int	floodfill(t_game *game, int	y, int x)
{
	if (x < 0 || y < 0 || x >= game->max_x || y >= game->max_y)
	{
		//printf("FAIL\n");
		return (1);
	}
	if (game->map[y][x] == WALL || game->map[y][x] == OK)
	{
		//printf("OK\n");
		return (0);
	}
	if (game->map[y][x] == EMPTY)
		printf("EMPTY\n");
	game->map[y][x] = OK;
	return (floodfill(game, y, x + 1) || floodfill(game, y, x -1)
	|| floodfill(game, y + 1, x) ||floodfill(game, y - 1, x));
}
