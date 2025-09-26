/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:15:40 by agaland           #+#    #+#             */
/*   Updated: 2025/09/26 17:17:16 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ft_error(char *msg, char *var)
{
	ft_printf_fd(STDERR_FILENO, "Error\n");
	if (var)
		ft_printf_fd(STDERR_FILENO, msg, var);
	else
		ft_printf_fd(STDERR_FILENO, msg);
}

void	print_int_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
		printf("%d ", arr[i]);
	printf("\n");
}

void	print_map(int **matrix, int height, int width)
{
	int	i;
	int	j;

	printf("------------ Print Map ------------\n");
	printf("\n");
	i = 0;
	while (i < height)
	{
		j = 0 ;
		while (j < width)
		{
			printf("%d", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("----------------------------------\n");
}
