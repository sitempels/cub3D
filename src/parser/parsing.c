/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:35:36 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 14:22:28 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

int	parse_config(char *line, int *arr, t_config *config)
{
	int		i;
	int		type;
	char	first_char;

	if (!detect_content(line, &first_char))
		return (0);
	if (first_char == '1')
	{
		config->first_map = ft_strdup(line);
		return (0);
	}
	i = 0;
	while (line[i] && ft_isblank(line[i]))
		i++;
	type = compare_types(&line[i]);
	if (type >= 0)
	{
		if (skip_and_save_type(type, arr, &i) != 0)
			return (1);
	}
	else
		return (ft_error(ERR_CONFIG, NULL), 1);
	if (parse_line(config, line, &i, type) == ERROR)
		return (1);
	return (0);
}

int	process_config(int fd, t_config *config)
{
	char	*line;
	int		parsed_elements[6];
	int		i;
	int		ret;

	i = 0;
	while (i < 6)
		parsed_elements[i++] = -1;
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (ft_error(RD_FILE, NULL), 1);
		if (parse_config(line, parsed_elements, config) == ERROR)
			return (gnl_cleanup(line), 1);
		free(line);
		if (config->first_map && config_completed(parsed_elements))
			return (0);
		else if (config->first_map)
			break ;
	}
	return (ft_error(MISSING_CONFIG, NULL), 1);
}

void	init_config(t_game *game)
{
	int	i;

	game->config = malloc(sizeof(t_config));
	if (!game->config)
	{
		ft_error(ERR_INIT_CONFIG, NULL);
		exit(ERR_MALLOC);
	}
	game->config->first_map = NULL;
	i = 0;
	while (i < 3)
	{
		game->config->floor_rgb[i] = 0;
		game->config->ceiling_rgb[i] = 0;
		i++;
	}
	game->config->map_end = false;
}

int	parse_file(int fd, t_game *game)
{
	init_config(game);
	if (process_config(fd, game->config) == ERROR)
		return (1);
	if (process_map_recursive(fd, game, &game->max_y, &game->max_x) == 1)
		return (1);
	print_map(game->map, game->max_y, game->max_x); //A SUPPRIMER
	if (check_map_closure(game) != 0)
		return (1);
	return (0);
}
