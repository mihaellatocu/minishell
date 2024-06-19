/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:22:50 by mtocu             #+#    #+#             */
/*   Updated: 2023/11/12 13:32:47 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_memalloc(int n, int len)
{
	char	*res;

	if (n == 0)
	{
		res = (char *)malloc(sizeof(char) + 1);
		res[0] = '0';
	}
	else if (n < 0)
	{
		res = (char *)malloc((len + 1) * sizeof(char));
		res[0] = '-';
	}
	else
		res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	res[len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = ft_count_len(n);
	res = ft_memalloc(n, len);
	if (n == -2147483648)
	{
		res[1] = '2';
		n = 147483648;
	}
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		res[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
	}
	return (res);
}
