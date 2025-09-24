/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/24 16:17:19 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

void	malloc_exit(t_game *game, char *line)
{
	ft_error(ERR_MALLOC, NULL);
	if (line)
		gnl_cleanup(line);
	else
		gnl_cleanup(NULL);
	cleanup_game(game);
	exit(EXIT_FAILURE);
}

void	free_map(int **array, int size)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void	gnl_cleanup(char *line)
{
	free(line);
	get_next_line(-1, NULL);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
	{
		free_map(game->map, game->max_y);
		game->map = NULL;
	}
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
	if (game->config)
		free_config(game->config);
}

void	free_config(t_config *config)
{
	int	i;

	if (config->first_map)
	{
		free(config->first_map);
		config->first_map = NULL;
	}
	i = 0;
	while (i < 4)
	{
		if (config->textures_path[i])
			free(config->textures_path[i]);
		i++;
	}
	free(config);
	config = NULL;
}
