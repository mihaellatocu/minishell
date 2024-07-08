/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:23:49 by mtocu             #+#    #+#             */
/*   Updated: 2024/03/19 19:39:15 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	unsigned char	*str;
	size_t			i;
	size_t			start;
	size_t			end;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_check_in_set(s1[start], set))
		start++;
	while (end > start && ft_check_in_set(s1[end - 1], set))
		end--;
	str = malloc(sizeof(char) * (end - start) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return ((char *)str);
}
/*
int	main(void)
{
	char *s1 = "abcdeefabc";
	char *s2 = "abc";
	printf("%s\n", ft_strtrim(s1, s2));
}*/
