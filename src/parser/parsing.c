/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:35:36 by agaland           #+#    #+#             */
/*   Updated: 2025/09/10 18:16:18 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../gnl/get_next_line_bonus.h"

bool	detect_content(char *line, char *first_char)
{
	int	i;

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
	if (c == 32 || c == 9 || 11 <= c && c <= 13)
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
		while (ft_isspace2(line[i]))
			i++;
		type = compare_types(&line[i]);
		if (type >= 0)
		{
			if (type == NO && arr[NO] == -1)
				i += 2;
			else 
				return (printf("Error: This type has already been parsed\n"), 1);
		}
		while (ft_isspace2(line[i]))
			i++;
		if (!line[i] || line[i] == '\n')
		{
			printf("Error: Missing config value");
			return (1);
		}
		if (!valid_file_extension(&line[i], ".xpm", 'X')) //logique a peaufiner, del pourrair etre ' ' aussi + verifier qu'aucun contenu ne se trouve apres.
			return (1);
		printf("Texture extension format validated\n");
		break ;
		//allocate_config();
	}
	return (0);
}

int	process_config(int fd, t_game *game)
{
	char	*line;
	int		arr[6];
	int		i;

	i = 0;
	while (i < 6)
		arr[i++] = -1;
	if ((get_next_line(fd, &line)) < 0)
		return (printf("Gnl Error\n"), 1);
	//print_int_arr(arr, 6);
	if (parse_config(line, arr) == 1)
		return (free(line), 1);
	free(line);
	return (0);
}

int	parse_file(int fd, t_game *game)
{
	int	rows;
	int	max_len;

	if (process_config(fd, game) == 1)
		return (1);
	rows = 0;
	max_len = 0;
	if (process_map_recursive(fd, &game->map, &rows, &max_len) == 1)
		return (1);
	print_map(game->map, rows, max_len);
	return (0);
}

int	check_line(char *line, int *player_count)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n", line[i]))
		{
			ft_printf_fd(STDERR_FILENO,
				"Error: Invalid character <%c> inserted\n", line[i]);
			return (1);
		}
		if (ft_strchr("NSEW", line[i]))
		{
			(*player_count)++;
			if (*player_count > 1)
			{
				ft_printf_fd(STDERR_FILENO, "Error: Multiple players found\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
