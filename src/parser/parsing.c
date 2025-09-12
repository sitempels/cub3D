/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:35:36 by agaland           #+#    #+#             */
/*   Updated: 2025/09/12 18:41:44 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line_bonus.h"

bool	detect_content(char *line, char *first_char)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
		{
			*first_char = line[i];
			return (true);
		}
		i++;
	}
	return (false);
}

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
	if (ft_strncmp(line_pos, "F ", 3) == 0)
		return (F);
	if (ft_strncmp(line_pos, "C ", 3) == 0)
		return (C);
	return (-1);
}

int	ft_isspace2(char c)
{
	if (c == 32 || c == 9 || (11 <= c && c <= 13))
		return (1);
	return (0);
}

int	parse_config(char *line, int *arr)
{
	int		i;
	char	first_char;
	int		type;

	if (!detect_content(line, &first_char))
		return (0);
	/* 	if (first_char == '1')
		//it's a map!!
	printf("first char: %c\n", first_char); */
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace2(line[i]))
			i++;
		type = compare_types(&line[i]);
		if (type >= 0)
		{
			if (type == NO && arr[NO] == -1)
				i += 2;
			else
				return (printf("Error: This type has already been parsed\n"), 1);
		}
		while (line[i] && ft_isspace2(line[i]))
			i++;
		if (!line[i] || line[i] == '\n')
		{
			printf("Error: Missing config value\n");
			return (1);
		}
		if (!valid_file_extension(&line[i], ".xpm", 'X')) //logique a peaufiner, del pourrair etre ' ' aussi + verifier qu'aucun contenu ne se trouve apres.
			return (1);
		printf("Texture extension format validated\n");
		while (ft_isalnum(line[i]) || line[i] == '.' || line[i] == '/')
			i++;
		if (detect_content(&line[i], &first_char))
		{
			printf("Invalid configuration informations.\n");
			return (1);
		}
		//allocate_config();
		break ;
	}
	return (0);
}

bool	config_completed(int *parsed_elements)
{
	int	i;

	i = 0;
	while (NO < C)
	{
		if (parsed_elements[i] == -1)
			return (false);
		i++;
	}
	return (true);
}

void init_config(t_config *config)
{
	int	i;
	
	config->first_map = NULL;
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	i = 0;
	while (i++ < 3)
	{
		config->floor_color[i] = 0;
		config->ceiling_color[i] = 0;
	}
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
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (printf("Gnl Error\n"), 1);
		if (config->first_map && !config_completed(parsed_elements))
			return (printf("Configuration incomplete\n"), 1);
		else	
			break;
		if (!line)
			return (printf("Missing map\n"), 1);
		if (parse_config(line, parsed_elements) == 1)
			return (1);
		free(line);
	}
	return (ret);
}

int	parse_file(int fd, t_game *game)
{
	init_config(game->config);
	if (process_config(fd, game->config) == 1)
		return (1);
	if (process_map_recursive(fd, game, &game->max_y, &game->max_x) == 1)
		return (free_config(game->config), 1);
	print_map(game->map, game->max_y, game->max_x);
	return (0);
}

int	check_line(char *line)
{
	int		i;
	static int	player_count;

	//char	first_char;

	i = 0;
	while (line[i])
	{
/* 		if (!detect_content(line, &first_char) || first_char != '1')
			return (printf("Error: invalid map\n"), 1); */
		if (!ft_strchr("01NSEW \n", line[i]))
		{
			ft_printf_fd(STDERR_FILENO,
				"Error: Invalid character <%c> inserted\n", line[i]);
			return (1);
		}
		if (ft_strchr("NSEW", line[i]))
		{
			player_count++;
			if (player_count > 1)
			{
				ft_printf_fd(STDERR_FILENO, "Error: Multiple players found\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
