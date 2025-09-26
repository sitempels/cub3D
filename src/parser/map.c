/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:15 by agaland           #+#    #+#             */
/*   Updated: 2025/09/26 16:15:25 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

static int	check_line(char *line, t_config *config)
{
	int	i;

	if (detect_content(line, NULL))
	{
		if (config->map_end == true)
			return (ft_error(ERR_MAP, NULL), 1);
	}
	else
		return (config->map_end = true, 0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n\t", line[i]))
			return (ft_printf_fd(STDERR_FILENO,
					"Error\nInvalid character <%c> on the map\n", line[i]), 1);
		if (ft_strchr("NSEW", line[i]))
		{
			config->player_count++;
			if (config->player_count > 1)
				return (ft_error(MULT_PLAYERS, NULL), 1);
		}
		i++;
	}
	return (0);
}

static size_t	no_nwl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

static int	get_line_map(t_game *game, int fd, char **line, int *line_lenght)
{
	int	ret;

	if (game->config->first_map)
	{
		*line = ft_strdup(game->config->first_map);
		if (!line)
			malloc_exit(game, NULL);
		free(game->config->first_map);
		game->config->first_map = NULL;
	}
	else
	{
		if ((get_next_line(fd, line)) < 0)
			return (ft_error(RD_FILE, NULL), 1);
		else if (!*line)
			return (0);
	}
	*line_lenght = no_nwl_strlen(*line);
	if (*line_lenght > game->max_x)
		game->max_x = *line_lenght;
	ret = check_line(*line, game->config);
	if (ret == 1)
		return (gnl_cleanup(*line), 1);
	return (0);
}

int	process_map_recursive(int fd, t_game *game)
{
	char		*line;
	int			line_lenght;
	int			curr_row;

	if (get_line_map(game, fd, &line, &line_lenght) == ERROR)
		return (1);
	if (!line)
		return (init_game(game, game->max_y));
	if (!game->config->map_end)
		curr_row = (game->max_y)++;
	if (process_map_recursive(fd, game) != 0)
		return (gnl_cleanup(line), 1);
	if (!game->map)
		return (gnl_cleanup(line), ft_error(ERR_MALLOC, NULL), 1);
	if (detect_content(line, NULL))
	{
		game->map[curr_row] = malloc(sizeof(int) * (game->max_x));
		if (!(game->map)[curr_row])
			malloc_exit(game, line);
		if (init_map(game, line, curr_row, line_lenght) != 0)
			return (free(line), 1);
	}
	return (free(line), 0);
}
