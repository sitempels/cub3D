#include "cub3D.h"

int	main(void)
{
	t_game	*game;
	int		i;

	game = (t_game *)malloc (sizeof(t_game));
	game->map = (int **) malloc(sizeof(int *) * 5);
	i = 0;
	while (i < 5)
	{
		game->map[i] = (int *) malloc(sizeof(int) * 5);
		i++;
	}
	game->map[0][0] = 1;
	game->map[0][1] = 1;
	game->map[0][2] = 1;
	game->map[0][3] = 1;
	game->map[0][4] = 1;
	game->map[1][0] = 1;
	game->map[1][1] = 0;
	game->map[1][2] = 0;
	game->map[1][3] = 0;
	game->map[1][4] = 1;
	game->map[2][0] = 1;
	game->map[2][1] = 0;
	game->map[2][2] = 0;
	game->map[2][3] = 0;
	game->map[2][4] = 1;
	game->map[3][0] = 1;
	game->map[3][1] = 0;
	game->map[3][2] = 0;
	game->map[3][3] = 0;
	game->map[3][4] = 1;
	game->map[4][0] = 1;
	game->map[4][1] = 1;
	game->map[4][2] = 1;
	game->map[4][3] = 1;
	game->map[4][4] = 1;
	game->player = (t_player *) malloc(sizeof(t_player));
	game->player->facing = 0;
	game->player->pos_x = 2;
	game->player->pos_y = 3;
	display_handler(game, 5, 5);
	return (0);
}
