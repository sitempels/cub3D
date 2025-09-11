/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:31 by agaland           #+#    #+#             */
/*   Updated: 2025/09/10 18:10:58 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
