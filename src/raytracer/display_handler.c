/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:46:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/19 16:33:46 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	display_handler(t_game *game)
{
	t_data	data;

	game->data = &data;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, game->screen_width, game->screen_height, "cub3D");
	data.img = mlx_new_image(data.mlx, game->screen_width, game->screen_height);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.l_length, &data.endian); 
	game->mini_width = MINI_SIZE * game->max_x;
	game->mini_height = MINI_SIZE * game->max_y;
	mlx_hook(data.win, 2, 1L << 0, key_handler, game);
	mlx_hook(data.win, 17, 0, close_all, &data);
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
	if (game->minimap == 1)
		draw_minimap(game, data);
//	printf("player main_loop	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos[0], game->player->pos[1]);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
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
