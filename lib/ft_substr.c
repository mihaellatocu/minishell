/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:15:29 by mtocu             #+#    #+#             */
/*   Updated: 2024/03/21 19:18:20 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	else if (start > (ft_strlen(s)))
		len = 0;
	else if ((ft_strlen(s)) - start <= len)
		len = (ft_strlen(s)) - start;
	str = malloc(sizeof(char) * len + 1);
	while (s && i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
}
/*
int	main(void)
{
	char *s = "abcdefghij";
	printf("%s\n", ft_substr(s, 5, 1));
}*/
