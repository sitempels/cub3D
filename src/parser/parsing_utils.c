/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:35:43 by agaland           #+#    #+#             */
/*   Updated: 2025/09/11 14:12:37 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	valid_file_extension(char *filename, char *ext, char flag)
{
	if (flag != 'X')
	{
		if (ft_strnstr_end(filename, ext, ft_strlen(filename)) != NULL)
			return (true);
	}
	else
	{
		if (ft_strnstr(filename, ext, ft_strlen(filename)) != NULL)
			return (true);
	}
	ft_printf_fd(STDERR_FILENO,
		"Error: incorrect or missing file extension. Expected: %s\n", ext);
	return (false);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strnstr_end(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		ptr = (char *) &haystack[i];
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
			j++;
		if (needle[j] == '\0' && haystack[i + j] == '\0')
			return (ptr);
		i++;
	}
	return (NULL);
}
