/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 21:43:37 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 02:15:50 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		return (ft_error(DOUBLE_TYPE, NULL), 1);
	return (0);
}

bool	is_texture(int type)
{
	if (type == NO || type == SO || type == WE || type == EA)
		return (true);
	return (false);
}
