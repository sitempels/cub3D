/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:46:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/24 18:27:51 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	print_fps(t_game *game, t_data *data);

int	cub3d(t_game *game)
{
	t_data			data;
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	game->start_time = tmp.tv_sec * 1000000 + tmp.tv_usec;
	game->old_time = 0;
	mlx_hook(data.win, 2, 1L << 0, key_handler, game);
//	mlx_hook(data.win, 17, 0,/**/ , &data);
	mlx_loop_hook(data.mlx, game_loop, game);
	mlx_loop(data.mlx);
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
	mlx_do_sync(data->mlx);
	if (game->minimap)
	{
		draw_minimap(game, data);
		draw_player(game, data, PLAYER_COLOR);
	}
	return (0);
}

void	get_fps(t_game *game)
{
	unsigned long int	diff;
	unsigned long int	time;
	struct timeval		tmp;

	gettimeofday(&tmp, NULL);
	time = (tmp.tv_sec * 1000000 + tmp.tv_usec - game->start_time) / 1000;
	diff = time - game->old_time;
	game->frametime = ((double)diff / 1000);
	game->old_time = time;
}

static void	print_fps(t_game *game, t_data *data)
{
	char	*frame;

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

void	img_put(t_data *data, int coord[2], int size_mod, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size_mod)
	{
		j = 0;
		while (j < size_mod)
		{
			px_put(data, (coord[0] + 1) * size_mod - i,
				(coord[1] + 1) * size_mod - j, color);
			j++;
		}
		i++;
	}
}
