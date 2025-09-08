/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:41:00 by stempels          #+#    #+#             */
/*   Updated: 2025/09/08 17:10:23 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	calc_frame(t_game *game)
{
	if (map[x][y] == WALL || map[x][y + 1] == WALL)

	return (0);
}

int	main(int ac, char **av)
{
	//t_game *game;
	
	if (ac != 2)
	{
		ft_printf_fd(STDERR_FILENO, "Wrong number of arguments\nUsage : ./cub3d <filename.cub>");
		return (1);
	}
	
	return 0;

}
