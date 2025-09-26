/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:56:44 by stempels          #+#    #+#             */
/*   Updated: 2025/09/26 17:05:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	get_angle(int type, int facing)
{
	double	res;

	if (type == 0)
	{
		if (facing == NORTH || facing == SOUTH)
			res = 0;
		else if (facing == EAST)
			res = 1;
		else if (facing == WEST)
			res = -1;
		else
			res = cosf(facing * M_PI / 180);
	}
	if (type == 1)
	{
		if (facing == EAST || facing == WEST)
			res = 0;
		else if (facing == NORTH)
			res = -1;
		else if (facing == SOUTH)
			res = 1;
		else
			res = sinf(facing * M_PI / 180);
	}
	return (res);
}

void	refresh_screen(t_game *game)
{
	int				i;
	int				j;
	unsigned int	color;

	i = -1;
	while (++i < game->screen_width)
	{
		j = -1;
		while (++j < game->screen_height)
		{
			if (game->minimap)
			{
				if (i < game->mini_width + MINI_BORDER_L)
					if (j < game->mini_height + MINI_BORDER_L)
						j = game->mini_height + MINI_BORDER_L;
			}
			if (j < game->screen_height / 2)
				color = convert_int(game->config->floor_rgb);
			if (j >= game->screen_height / 2)
				color = convert_int(game->config->ceiling_rgb);
			px_put(game->data, i, j, color);
		}
	}
	return ;
}

unsigned int	convert_int(int rgb[3])
{
	unsigned int	res;

	res = 0;
	res = (rgb[0]);
	res = (res << 8) + rgb[1];
	res = (res << 8) + rgb[2];
	return (res);
}
