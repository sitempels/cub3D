/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:35:36 by agaland           #+#    #+#             */
/*   Updated: 2025/09/16 19:22:02 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

int	compare_types(char *line_pos)
{
	if (ft_strncmp(line_pos, "NO ", 3) == 0)
		return (NO);
	if (ft_strncmp(line_pos, "SO ", 3) == 0)
		return (SO);
	if (ft_strncmp(line_pos, "WE ", 3) == 0)
		return (WE);
	if (ft_strncmp(line_pos, "EA ", 3) == 0)
		return (EA);
	if (ft_strncmp(line_pos, "F ", 2) == 0)
		return (F);
	if (ft_strncmp(line_pos, "C ", 2) == 0)
		return (C);
	return (-1);
}

bool	config_completed(int *parsed_elements)
{
	int	i;

	i = 0;
	while (i <= C)
	{
		if (parsed_elements[i] == -1)
			return (false);
		i++;
	}
	return (true);
}

int	skip_and_save_type(int type, int *arr, int *i)
{
	if (is_texture(type) && arr[type] == -1)
	{
		arr[type] = type;
		*i += 2;
	}
	else if ((type == F || type == C) && arr[type] == -1)
	{
		arr[type] = type;
		*i += 1;
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "Error: This type has already been parsed\n");
		return (1);
	}
	return (0);
}

bool	is_texture(int type)
{
	if (type == NO || type == SO || type == WE || type == EA)
		return (true);
	return (false);
}

int	check_rgb(char *line, int *i, t_config *config, int type)
{
	int		count;
	char	*start;

	start = &line[*i];
	count = 0;
	while (*start && ft_isblank(*start))
		start++;

	while (count < 3)
	{
		if (!ft_isdigit(*start))
			return (ft_printf_fd(STDERR_FILENO, "Error: Invalid RGB format\n"), 1);
		if (type == C)
			config->ceiling_color[count] = atoi(start);
		else
			config->floor_color[count] = atoi(start);
		if ((config->ceiling_color[count] < 0 || config->ceiling_color[count] > 255) ||
				(config->floor_color[count] < 0 || config->floor_color[count] > 255))
				return (ft_printf_fd(STDERR_FILENO, "Error: RGB value out of range (0-255)\n"), 1);
		while (*start && ft_isdigit(*start))
			start++;
		count++;
		if (count < 3)
		{
			while (*start && ft_isblank(*start))
				start++;
			if (*start  != ',')
				return (ft_printf_fd(STDERR_FILENO, "Error: RGB values must be separated by a comma\n"), 1);
			start++;
			while (*start && ft_isblank(*start))
				start++;
		}
	}			
	if (count != 3)
		return (ft_printf_fd(STDERR_FILENO, "Error: RGB must have exactly 3 values\n"), 1);
	while (*start && ft_isblank(*start))
		start++;
	if (*start && *start != '\n' && *start != '\0')
		return (ft_printf_fd(STDERR_FILENO, "Error: Extra content after RGB values\n"), 1);
	*i = start - line;
	return (0);
}

int	parse_config(char *line, int *arr, t_config *config)
{
	int		i;
	char	first_char;
	int		type;

	if (!detect_content(line, &first_char))
		return (0);
	if (first_char == '1')
	{
		printf("it's a map!! : %c\n", first_char);
		config->first_map = ft_strdup(line);
		return (0);
	}
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isblank(line[i]))
			i++;
		type = compare_types(&line[i]);
		if (type >= 0)
		{
			if (skip_and_save_type(type, arr, &i) != 0)
				return (1);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, "Error: Incorrect config value\n");
			return (1);
		}
		while (line[i] && ft_isblank(line[i]))
			i++;
		if (!line[i] || line[i] == '\n')
		{
			ft_printf_fd(STDERR_FILENO, "Error: Missing config value\n");
			return (1);
		}
		if (is_texture(type))
		{
			char	*start;
			
			if (!valid_file_extension(&line[i], ".xpm", 'X'))
				return (1);
			start = &line[i];
			printf("Texture extension format validated\n");
			while (ft_isalnum(line[i]) || line[i] == '.' || line[i] == '/' || line[i] == '_')
				i++;
			if (detect_content(&line[i], &first_char))
			{
				ft_printf_fd(STDERR_FILENO, "Error: Extra content after texture path\n");
				return (1);
			}
			int	len = &line[i + 1] - start; // sans + 1 n'enregistre que jusque "./path_texture.xp" sans le 'm'
			char *path = malloc(sizeof(char) * (len + 1));
			if (!path)
				return (1);
			ft_strlcpy(path, start, len);
			path[len] = '\0';
			if (type == NO)
				config->no_texture = path;
			else if (type == SO)
				config->so_texture = path;
			else if (type == WE)
				config->we_texture = path;
			else if (type == EA)
				config->ea_texture = path;
		}
		else
		{
			if (check_rgb(line, &i, config, type) != 0)
				return (1);
			printf("RGV value validated\n");
		}
		break ;
	}
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
			return (ft_printf_fd(STDERR_FILENO, "Error: Reading file"), 1);
		if (parse_config(line, parsed_elements, config) == 1)
			return (gnl_cleanup(line), 1);
		free(line);
		if (config->first_map && config_completed(parsed_elements))
			return (0);
		if (config->first_map)
		{
			ft_printf_fd(STDERR_FILENO, "Error: incomplete configuration\n");
			return (1);
		}
	}
	ft_printf_fd(STDERR_FILENO, "Error: incomplete configuration\n");
	return (ret);
}

int	parse_file(int fd, t_game *game)
{	
	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (1);
	init_config(game->config);
	if (process_config(fd, game->config) == 1)
		return (1);
	if (process_map_recursive(fd, game, &game->max_y, &game->max_x) == 1)
		return (1);
	print_map(game->map, game->max_y, game->max_x);
	if (check_map_closure(game) != 0)
	{
		return (1);
	}
/* 	if (floodfill(game, (int)(game->player->pos[0] - 0.5), (int)(game->player->pos[1] - 0.5)) != 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error : Map is not closed\n");
		return (1);
	} */
	//print_map(game->map, game->max_y, game->max_x);
	return (0);
}

void init_config(t_config *config)
{
	int	i;
	
	if (config)
	{
		config->first_map = NULL;
		config->no_texture = NULL;
		config->so_texture = NULL;
		config->we_texture = NULL;
		config->ea_texture = NULL;
		i = 0;
		while (i < 3)
		{
			config->floor_color[i] = 0;
			config->ceiling_color[i] = 0;
			i++;
		}
		config->map_end = false;
	}
}