/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:37:24 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 19:38:56 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*manipulate the string from token list, removing the $env/word and replace 
it with value of the matching key*/
static char	*create_new_wd(char *current_word, char *env, char *to_replace, int start)
{
	int		i;
	int		j;
	char	*new_word;

	i = -1;
	j = 0;
	new_word = (char *)malloc((ft_strlen(current_word) + ft_strlen(to_replace)
				- ft_strlen(env) + 1) * sizeof(char));
	if (!new_word)
		return (current_word);
	while (++i < start)
		new_word[i] = current_word[i];
	while (to_replace[j] != '\0')
		new_word[i++] = to_replace[j++];
	j = ft_strlen(env) + start;
	if (ft_strncmp(env, "$?", ft_strlen(env)) != 0)
		j++;
	while (current_word[j] != '\0')
		new_word[i++] = current_word[j++];
	new_word[i] = '\0';
	free (current_word);
	free(to_replace);
	return (new_word);
}

/*Comparing the word after $ char with key value in the env list
	and returning a string/word with the value of the key*/
static char	*replace_dollar_sign(char *word, t_env_list *env_list, int status)
{
	char		*to_replace;
	t_env_list	*current_env;

	to_replace = NULL;
	if (strncmp(word, "$?", ft_strlen(word)) == 0)
	{
		to_replace = ft_itoa(status);
		return (to_replace);
	}
	current_env = env_list;
	while (current_env != NULL)
	{
		if ((ft_strlen(word) == ft_strlen(current_env->key)) && \
			ft_strncmp(word, current_env->key, ft_strlen(word)) == 0)
			to_replace = ft_strdup(current_env->value);
		current_env = current_env->next;
	}
	if (to_replace == NULL)
		to_replace = ft_strdup("");
	return (to_replace);
}

/*Looking for $ sign to count how many time we loop to replace variables*/
int	count_how_many_dollar_signs(char *str)
{
	int	i;
	int	ctr;

	i = 0;
	ctr = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && ((ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?')))
			ctr++;
		i++;
	}
	return (ctr);
}

/*serching for the $ char and returning its position*/
int	ft_find_dollar(char *str, char **word, int i)
{
	int	start;
	int	end;

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
	while (str[++i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0' && (str[i + 1] == '_' || \
		ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
		{
			start = i + 1;
			break ;
		}
	}
	end = start;
	if (start != -1)
	{
		while (ft_isalnum(str[end]) || str[end] == '_')
			end++;
		*word = ft_substr(str, start, end - start);
	}
	return (--start);
}

void	find_dollar_sign_and_replace(t_shell *p)
{
	t_lst	*current;
	int		count;
	char	*word;
	int		i;

	current = p->token_list;
	while (current)
	{
		word = NULL;
		if (current->token == WORD || current->token == DQUOTE)
		{
			count = count_how_many_dollar_signs(current->content);
			while (count > 0)
			{
				i = ft_find_dollar(current->content, &word, -1);
				if (i >= 0)
					current->content = create_new_wd(current->content, word, \
					replace_dollar_sign(word, p->envir, p->command_status), i);
				if (word)
					free(word);
				count--;
			}
		}
		current = current->next;
	}
}