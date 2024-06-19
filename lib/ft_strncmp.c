/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:25:15 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/04 16:05:44 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Pay attention that the comparison is done using unsigned char
It doesn't really matter when checking for equality
because it is going to be the same either way.
But make sure to convert to unsigned char in the difference.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			if (s1[i] > s2[i])
				return (1);
			else if (s1[i] < s2[i])
				return (-1);
		}
	}
	return (0);
}

/*

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n)
	{
		while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	main(void)
{
	char *s1 = "ab";
	char *s2 = "aa";
	printf("%d\n", ft_strncmp(s1, s2, 3));
	
	//printf("%d\n", strncmp(s1, s2, 3));
}*/
