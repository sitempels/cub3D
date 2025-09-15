#include "cub3D.h"

int	check_borders(t_game game)
{
	if (1)
	{
		printf("test: %s\n", game.config->no_texture);
		return (0);
	}
	return (1);

}

int	floodfill(t_game game)
{
	if (check_borders(game) != 0)
		return (1);
	return 0;
}