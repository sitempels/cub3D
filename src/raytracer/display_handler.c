/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:46:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/24 14:11:02 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	display_handler(t_game *game)
{
	struct timeval	tmp;
	t_data	data;
	int		i;

	game->data = &data;
	gettimeofday(&tmp, NULL);
	game->start_time = tmp.tv_sec * 1000000 + tmp.tv_usec;;
	game->old_time = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, game->screen_width, game->screen_height, "cub3D");
	data.img = mlx_new_image(data.mlx, game->screen_width, game->screen_height);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.l_length, &data.endian); 
	i = 0;
	while (i < 1)
	{
		game->texture[i] = malloc(sizeof(t_texture));
		if (!game->texture[i])
			return (1);
		game->texture[i]->wall = mlx_xpm_file_to_image(data.mlx, game->config->textures_path[i], &game->texture[i]->width, &game->texture[i]->height);
		if (!game->texture[i]->wall)
			return (1);
		game->texture[i]->addr_w = mlx_get_data_addr(game->texture[i]->wall, &game->texture[i]->bpp, &game->texture[i]->l_length, &game->texture[i]->endian);
		i++;
	}
	game->default_color[NO] = 0xff000050;
	game->default_color[SO] = 0xff000025;
	game->default_color[EA] = 0xff005000;
	game->default_color[WE] = 0xff002500;
	game->mini_width = MINI_SIZE * game->max_x;
	game->mini_height = MINI_SIZE * game->max_y;
//	if (game->minimap == 1)
//		draw_minimap(game, &data);
	mlx_hook(data.win, 2, 1L << 0, key_handler, game);
	mlx_hook(data.win, 17, 0, close_all, &data);
	mlx_loop_hook(data.mlx, game_loop, game);
	if (game->minimap == 1)
		draw_minimap(game, &data);
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
	{
		mlx_string_put(data->mlx, data->win, game->screen_width - 128, 32, 0xffffff, "FPS");
		mlx_string_put(data->mlx, data->win, game->screen_width - 64, 32, 0xffffff, ft_itoa((int)(1 / game->frametime)));
	}
//	else
//		mlx_string_put(data->mlx, data->win, game->screen_width - 128, 32, 0xffffff, " ");
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
			px_put(data, (coord[0] + 1) * size_mod - i, (coord[1] + 1) * size_mod - j, color);
			j++;
		}
		i++;
	}
}

void	px_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return ;
	dst = data->addr + (y * data->l_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
