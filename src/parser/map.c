/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:15 by agaland           #+#    #+#             */
/*   Updated: 2025/09/11 14:40:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

int	allocate_matrix(int ***matrix, int rows)
{
	*matrix = malloc(sizeof(int *) * (rows));
	if (!*matrix)
		return (1);
	return (0);
}

int	init_matrix(int ***matrix, char *line, int max_len, int curr_row, int line_lenght)
{
	int	j;

	j = 0;
	while (j < max_len)
	{
		(*matrix)[curr_row][j] = -1;
		j++;
	}
	j = 0;
	while (j < line_lenght)
	{
		if (line[j] == ' ' || line[j] == '\n')
			(*matrix)[curr_row][j] = EMPTY;
		else if (line[j] == '0')
			(*matrix)[curr_row][j] = FLOOR;
		else if (line[j] == '1')
			(*matrix)[curr_row][j] = WALL;
		else if (line[j] == 'N')
			(*matrix)[curr_row][j] = N;
		else if (line[j] == 'S')
			(*matrix)[curr_row][j] = S;
		else if (line[j] == 'E')
			(*matrix)[curr_row][j] = E;
		else if (line[j] == 'W')
			(*matrix)[curr_row][j] = W;
		else
			return (1);
		j++;
	}
	return (0);
}

int	process_map_recursive(int fd, int ***matrix, int *rows, int *max_len)
{
	char		*line;
	int			line_lenght;
	int			curr_row;
	static int	player_count;

	if ((get_next_line(fd, &line)) < 0)
		return (printf("Gnl Error\n"), 1);
	else if (!line)
		return (allocate_matrix(matrix, *rows));
	line_lenght = ft_strlen(line);
	if (line_lenght > *max_len)
		*max_len = line_lenght;
	curr_row = *rows;
	if (check_line(line, &player_count) == 1)
		return (1);
	(*rows)++;
	process_map_recursive(fd, matrix, rows, max_len);
	if (!*matrix)
		return (1);
	(*matrix)[curr_row] = malloc(sizeof(int) * (*max_len));
	if (!(*matrix)[curr_row])
		return (1);
	if (init_matrix(matrix, line, *max_len, curr_row, line_lenght) != 0)
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}
