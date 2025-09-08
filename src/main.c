/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:36:10 by stempels          #+#    #+#             */
/*   Updated: 2025/09/08 16:53:47 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

bool	check_file_ext(char *filename, char *ext)
{
	if (ft_strnstr(filename, ext, ft_strlen(filename)) != NULL)
		return (true);
	return true;
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