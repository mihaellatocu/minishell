/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:40:46 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/08 18:35:09 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		++i;
	while (src[j] != '\0' && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		++j;
	}
	if (i + j < size)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
/*
int	main(void)
{
	char a[30] = "";
	char *b = "123";
	printf("%zu\n", ft_strlcat(a, b, 3));
	printf("%s\n", a);
}*/
