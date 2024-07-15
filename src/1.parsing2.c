/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.parsing2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 13:05:40 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 13:05:40 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	operator(int c)
{
	if (c == PIPE || c == LESS || c == DLESS || c == DGREAT || c == '&' || \
		c == GREAT)
		return (true);
	return (false);
}

char	*find_word(char *s, size_t *i, t_token token)
{
	char	*word;
	size_t	start;
	size_t	index;

	start = *i;
	index = 0;
	if ((char)token == WORD)
		while (!ft_isspace((int)s[*i]) && !operator((int)s[*i]) && s[*i])
			(*i)++;
	else
	{
		start++;
		while (s[++(*i)] != (char)token)
			;
	}
	word = (char *)malloc((*i - start + 2) * sizeof(char));
	if (!word)
		ft_malloc_error();
	while (start < *i)
		word[index++] = s[start++];
	word[index] = '\0';
	if (token == WORD)
		(*i)--;
	return (word);
}
