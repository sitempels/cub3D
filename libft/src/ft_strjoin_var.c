/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:17:11 by stempels          #+#    #+#             */
/*   Updated: 2025/07/07 10:57:38 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static char	*call_recu(int nbr_str, va_list args, size_t i);

char	*ft_strjoin_var(int nbr_str, ...)
{
	char	*str;
	va_list	args;

	va_start(args, nbr_str);
	str = call_recu(nbr_str, args, 0);
	if (!str)
		return (NULL);
	va_end(args);
	return (str);
}

static char	*call_recu(int nbr_str, va_list args, size_t i)
{
	size_t	size;
	char	*to_join;
	char	*str;
	size_t	j;

	if (nbr_str == 0)
	{
		str = (char *) malloc(sizeof(char) * (i + 1));
		if (!str)
			return (NULL);
		str[i] = '\0';
		return (str);
	}
	to_join = va_arg(args, char *);
	size = ft_strlen(to_join);
	str = call_recu(nbr_str - 1, args, i + size);
	if (!str)
		return (NULL);
	j = 0;
	while (j < size)
	{
		str[i + j] = to_join[j];
		j++;
	}
	return (str);
}
