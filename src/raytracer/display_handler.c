/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:46:32 by stempels          #+#    #+#             */
/*   Updated: 2025/09/09 14:15:30 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	px_put(t_data *data, int x, int y, unsigned int color);
int	game_loop(t_game *game, t_data *data);

int	display_handler(t_game *game, int max_x, int max_y)
{
	int		i;
	int		j;
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	game->data = data;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->l_length, &data->endian); 
	mlx_hook(data->win, 2, 1L << 0, key_handler, game);
	mlx_hook(data->win, 17, 0, close_all, data);
	i = 0;
	while (i < max_x)
	{
		j = 0;
		while (j < max_y)
		{
			if (game->map[i][j] == EMPTY)
				img_put(data, i, j, EMPTY_COLOR);
			if (game->map[i][j] == WALL)
				img_put(data, i, j, WALL_COLOR);
			j++;
		}
		i++;
	}
	img_put(data, game->player->pos_x, game->player->pos_y, PLAYER_COLOR);
	printf("player main_loop	facing: %f posx: %f posy: %f\n", game->player->facing, game->player->pos_x, game->player->pos_y);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}

void	img_put(t_data *data, float x, float y, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE_MOD)
	{
		j = 0;
		while (j < SIZE_MOD)
		{
			px_put(data, (x + 1) * SIZE_MOD - i, (y + 1) * SIZE_MOD - j, color);
			j++;
		}
		i++;
	}
}

static void	px_put(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return ;
	dst = data->addr + (y * data->l_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}
