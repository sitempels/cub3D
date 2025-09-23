/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:37:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 14:37:33 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_line(char *line, t_config *config)
{
	int			i;
	static int	player_count;

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
					"Error\nInvalid character <%c> inserted\n", line[i]), 1);
		if (ft_strchr("NSEW", line[i]))
		{
			player_count++;
			if (player_count > 1)
				return (ft_error(MULT_PLAYERS, NULL), 1);
		}
		i++;
	}
	return (0);
}
