/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-15 13:04:07 by mtocu             #+#    #+#             */
/*   Updated: 2024-07-15 13:04:07 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_find_dollar_helper(char *str, char **word, int i, int *start)
{
	int	end;

	while (str[++i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && (str[i + 1] == '_' || \
		ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
		{
			*start = i + 1;
			break ;
		}
	}
	end = *start;
	if (*start != -1)
	{
		while (ft_isalnum(str[end]) || str[end] == '_')
			end++;
		*word = ft_substr(str, *start, end - *start);
	}
}

/*serching for the $ char and returning its position*/
int	ft_find_dollar(char *str, char **word, int i)
{
	int	start;

	while (str[++i])
	{
		if (str[i + 1] != '\0' && str[i] == '$' && str[i + 1] == '?')
		{
			*word = ft_strdup("$?");
			return (i);
		}
	}
	i = -1;
	start = -1;
	ft_find_dollar_helper(str, word, i, &start);
	return (--start);
}

/*Check if the token is an operator*/
bool	is_operator(t_lst *current)
{
	if (current->token == DLESS || current->token == LESS
		|| current->token == DGREAT || current->token == GREAT
		|| current->token == PIPE)
		return (true);
	return (false);
}
