/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 16:40:26 by agaland          ###   ########.fr       */
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

void	ft_error(char *msg, char *var)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	if (var)
		ft_printf_fd(STDERR_FILENO, msg, var);
	else
		ft_printf_fd(STDERR_FILENO, msg);
}

void	free_map(int **array, int size)
{
	int	i;
	
	if (!array)
		return;
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
		return;
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
