/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:12:26 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/04 19:41:39 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	const char *s = "lacasa";
	int c = 0;
	char *pointer = ft_strchr(s, c);
	printf("%p\n", &c);
	printf("%p\n", s);
	printf("%p\n", pointer);
	printf("%p\n", ft_strchr(s, c));
	return (0);
}*/
