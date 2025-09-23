/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:13:21 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 16:36:41 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_rgb(char **start, int *count, int type, t_config *config)
{
	if (!ft_isdigit(**start))
		return (ft_error(ERR_RGB, NULL), 1);
	if (type == C)
		config->ceiling_rgb[*count] = atoi(*start);
	else
		config->floor_rgb[*count] = atoi(*start);
	if ((config->ceiling_rgb[*count] < 0 || config->ceiling_rgb[*count] > 255)
		|| (config->floor_rgb[*count] < 0 || config->floor_rgb[*count] > 255))
		return (ft_error(RANGE_RGB, NULL), 1);
	while (**start && ft_isdigit(**start))
		(*start)++;
	(*count)++;
	if (*count < 3)
	{
		while (**start && ft_isblank(**start))
			(*start)++;
		if (**start != ',')
			return (ft_error(FRMT_RGB, NULL), 1);
		(*start)++;
		while (**start && ft_isblank(**start))
			(*start)++;
	}
	return (0);
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
		if (parse_rgb(&start, &count, type, config) == ERROR)
			return (1);
	}
	if (count != 3)
		return (ft_error(RGB_COUNT, NULL), 1);
	while (*start && ft_isblank(*start))
		start++;
	if (*start && *start != '\n' && *start != ' ')
		return (ft_error(RGB_EXTRA, NULL), 1);
	*i = start - line;
	return (0);
}

int	fill_texture(t_config *config, char *line, int *i, int type)
{
	char	*start;
	char	*path;
	char	first_char;
	int		len;

	if (!valid_file_extension(&line[*i], ".xpm", 'X'))
		return (1);
	start = &line[*i];
	printf("Texture extension format validated\n"); // COMMENTAIRE A SUPPRIMER
	while (ft_isalnum(line[*i]) || line[*i] == '.' || line[*i] == '-'
		|| line[*i] == '/' || line[*i] == '_')
		(*i)++;
	if (detect_content(&line[*i], &first_char))
		return (ft_error(EXTRA_CONTENT, NULL), 1);
	len = &line[*i] - start;
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return (1);
	ft_strlcpy(path, start, len + 1);
	config->textures_path[type] = path;
	return (0);
}

int	parse_line(t_config *config, char *line, int *i, int type)
{
	while (line[*i] && ft_isblank(line[*i]))
		(*i)++;
	if (!line[*i] || line[*i] == '\n')
	{
		ft_error(MISSING_CONFIG, NULL);
		return (1);
	}
	if (is_texture(type))
	{
		if (fill_texture(config, line, i, type) == ERROR)
			return (1);
	}
	else
	{
		if (check_rgb(line, i, config, type) == ERROR)
			return (1);
		printf("RGB value validated\n"); // COMMENTAIRE A SUPPRIMER
	}
	return (0);
}
