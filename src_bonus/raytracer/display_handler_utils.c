/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:52:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/26 17:05:36 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	free_texture(t_game *game);

int	key_handler(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_all(game);
	else if (keycode == W_KEY || keycode == S_KEY
		|| keycode == A_KEY || keycode == D_KEY
		|| keycode == LEFT_KEY || keycode == RIGHT_KEY)
		move_handler(game, keycode);
	else if (keycode == COMMA_KEY || (F_KEY <= keycode && keycode <= H_KEY))
		toggle_handler(game, keycode);
	return (0);
}

float	safe_angle_add(float *angle, float mod)
{
	*angle += mod;
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
	return (*angle);
}

int	close_all(t_game *game)
{
	int	status;

	status = 0;
	status = clean_all(game);
	exit (status);
}

int	clean_all(t_game *game)
{
	t_data	*data;

	if (!game)
		return (1);
	data = game->data;
	free_texture(game);
	cleanup_game(game);
	if (game->data)
	{
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			mlx_destroy_display(data->mlx);
		if (data->mlx)
			free(data->mlx);
		free(data);
	}
	return (0);
}

static void	free_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i])
		{
			if (game->texture[i]->wall)
				mlx_destroy_image(game->data->mlx, game->texture[i]->wall);
			free(game->texture[i]);
			game->texture[i] = NULL;
		}
		i++;
	}
}
