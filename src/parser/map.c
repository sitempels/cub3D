/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:15 by agaland           #+#    #+#             */
/*   Updated: 2025/09/12 01:05:03 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

int	init_game_struct(t_game *game, int rows, int max_len)
{
	game->map = malloc(sizeof(int *) * (rows));
	if (!game->map)
		return (1);
	game->max_x = max_len;
	game->max_y = rows;
	game->minimap = 1;
	game->fov = FOV;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (1);
	ft_memset(game->player, 0, sizeof(t_player));
	return (0);
}

void	pad_map_row(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < game->max_x)
	{
		game->map[y][x] = -1;
		x++;
	}
}

void	init_player(t_game *game, int y, int x, double facing)
{
	game->player->facing = facing;
	game->player->pos[0] = (y + 0.5);
	game->player->pos[1] = (x + 0.5);
	game->map[y][x] = FLOOR;
}

int	init_map(t_game *game, char *line, int curr_row, int line_lenght)
{
	int	j;

	pad_map_row(game, curr_row);
	j = 0;
	while (j < line_lenght)
	{
		if (line[j] == ' ' || line[j] == '\n')
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

void	gnl_cleanup(void)
{
	char *line;
	
	while (get_next_line(-1, &line) > 0)
		free(line);
}

int	process_map_recursive(int fd, t_game *game, int *rows, int *max_len)
{
	char		*line;
	int			line_lenght;
	int			curr_row;

	if ((get_next_line(fd, &line)) < 0)
		return (printf("Gnl Error\n"), 1);
	else if (!line)
		return (init_game_struct(game, *rows, *max_len));
	line_lenght = ft_strlen(line);
	if (line_lenght > *max_len)
		*max_len = line_lenght;
	curr_row = *rows;
	if (check_line(line) == 1)
		return (free(line), 1);
	(*rows)++;
	if (process_map_recursive(fd, game, rows, max_len) != 0)
		return (gnl_cleanup(), free(line), 1);
	if (!game->map)
		return (free(line), 1);
	game->map[curr_row] = malloc(sizeof(int) * (*max_len));
	if (!(game->map)[curr_row])
		return (free(line), 1);
	if (init_map(game, line, curr_row, line_lenght) != 0)
		return (free(line), 1);
	free(line);
	return (0);
}
