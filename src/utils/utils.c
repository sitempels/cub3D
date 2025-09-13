/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/13 18:02:10 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

void	print_int_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
		printf("%d ", arr[i]);
	printf("\n");
}

void	print_map(int **matrix, int height, int width)
{
	int	i;
	int	j;

	printf("------------ Print Map ------------\n");
	printf("\n");
	i = 0;
	while (i < height)
	{
		j = 0 ;
		while (j < width)
		{
			printf("%d", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("----------------------------------\n");
}

void	gnl_cleanup(char *line)
{
	free(line);
	get_next_line(-1, NULL);
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return;
	if (game->map)
	{
		i = 0;
		while (i < game->max_x)
		{
			if (game->map[i])
				free(game->map[i]);
			i++;
		}
		free(game->map);
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
	// penser a tout assigner a NULL blablabla
	if (config->first_map)
		free(config->first_map);
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->no_texture)
		free(config->we_texture);
	if (config->no_texture)
		free(config->we_texture);
	if (config->no_texture)
		free(config->ea_texture);
	if (config->no_texture)
		free(config->ea_texture);
}
