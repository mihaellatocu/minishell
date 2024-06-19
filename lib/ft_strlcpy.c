/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:11:59 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/06 19:12:09 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, int dest_size)
{
	int	source_size;
	int	i;

	if (!dst || !src)
		return (0);
	source_size = ft_strlen(src);
	i = 0;
	if (dest_size != 0)
	{
		while (src[i] != '\0' && i < (dest_size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (source_size);
}
/*
int	main(void)
{
	char dest[50] ="ab";
	const char *src = "abracadabra";
	ft_strlcpy(dest, src, 50);
	//printf("%i\n", strlcpy(dest, src, 2));
	printf("%zu\n", ft_strlcpy(dest, src, 50));
}*/
