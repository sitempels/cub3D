/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:46:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/25 18:02:35 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//static int	game_prep(t_game *game);
static void	print_fps(t_game *game, t_data *data);

int	cub3d(t_game *game)
{
	t_data			*data;
	struct timeval	tmp;

	data = game->data;
	gettimeofday(&tmp, NULL);
	game->start_time = tmp.tv_sec * 1000000 + tmp.tv_usec;
	game->old_time = 0;
	if (game->minimap)
	{
		draw_minimap(game, data);
		draw_player(game, data, PLAYER_COLOR);
	}
	mlx_hook(data->win, 2, 1L << 0, key_handler, game);
	mlx_hook(data->win, 17, 0, close_all, game);
	mlx_loop_hook(data->mlx, game_loop, game);
	mlx_loop(data->mlx);
	return (0);
}

int	game_loop(t_game *game)
{
	t_data	*data;

	data = game->data;
	refresh_screen(game);
	dda_operation(game, game->player->facing);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	get_fps(game);
	printf("old_time: %ld	frametime: %f\n", game->old_time, game->frametime);
	if (game->show_fps == 1)
		print_fps(game, data);
	if (game->minimap)
		draw_player(game, data, PLAYER_COLOR);
	mlx_do_sync(data->mlx);
	return (0);
}

void	get_fps(t_game *game)
{
	unsigned long int	diff;
	unsigned long int	time;
	struct timeval		tmp;

	gettimeofday(&tmp, NULL);
	time = (tmp.tv_sec * 1000000 + tmp.tv_usec - game->start_time) / 1000;
	if (time <= game->old_time)
		game->frametime = 0;
	else
	{
		diff = time - game->old_time;
		game->frametime = ((double)diff / 1000);
		game->old_time = time;
	}
}

static void	print_fps(t_game *game, t_data *data)
{
	char	*frame;

	frame = 0;
	if (game->frametime)
		frame = ft_itoa((int)(1 / game->frametime));
	if (!frame)
		return ;
	mlx_string_put(data->mlx, data->win, game->screen_width - 128,
		32, 0xd5b60a, "FPS");
	mlx_string_put(data->mlx, data->win, game->screen_width - 64,
		32, 0xd5b60a, frame);
	free(frame);
	return ;
}
