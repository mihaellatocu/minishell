/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:20:04 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/05 20:07:05 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function return the operator that is found*/
static t_token	find_token(char *str, size_t *i)
{
	if (str[*i] == '|')
		return (PIPE);
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i)++;
		return (DLESS);
	}
	else if (str[*i] == '<')
		return (LESS);
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		(*i)++;
		return (DGREAT);
	}
	else
		return (GREAT);
}

static bool	operator(int c)
{
	if (c == PIPE || c == LESS || c == DLESS || c == DGREAT || c == '&' || \
		c == GREAT)
		return (true);
	return (false);
}

char	*find_word(char *line, size_t *i, t_token token)
{
	char	*word;
	size_t	start;
	size_t	index;

	start = *i;
	index = 0;
	if ((char)token == WORD)
		while (!ft_isspace((int)line[*i]) && !operator((int)line[*i]) && line[*i] != '\0')
			(*i)++;
	else
	{
		start++;
		while (line[++(*i)] != (char)token)
			;
	}
	word = (char *)malloc((*i - start + 2) * sizeof(char));
	// if (!word) // to be added
	// 	error(1);
	while (start < *i)
		word[index++] = line[start++];
	word[index] = '\0';
	if (token == WORD)
		(*i)--;
	return (word);
}

//split the line in words and tokens, wc -l | ls -> 4 tokens
t_lst	*split_into_tokens(char *line, t_shell *p)
{
	size_t	i;
	size_t	length;

	i = -1;
	length = ft_strlen(line);
	while (++i < length)
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			lstadd_back(&p->token_list, lstnew(NULL, find_token(line, &i)));
		else if (line[i] == '\'')
			lstadd_back(&p->token_list, lstnew(find_word(line, &i, SQUOTE), SQUOTE));
		else if (line[i] == '\"')
			lstadd_back(&p->token_list, lstnew(find_word(line, &i, DQUOTE), DQUOTE));
		else if (ft_isalnum(line[i]) || line[i] == '-' || line[i] == '.' || line[i] == '=' || \
			line[i] == '/' || line[i] == '$' || line[i] == '*' || line[i] == '_')
			lstadd_back(&p->token_list, lstnew(find_word(line, &i, WORD), WORD));
	}
	return (p->token_list);
}

int	get_arg_count(t_lst *node)
{
	int	count;

	count = 0;
	while (node != NULL && node->token != PIPE)
	{
		if (node->type == CMD || node->type == ARG)
			count++;
		node = node->next;
	}
	return (count);
}

/* create a list of arguments on each node , and move the tokens node if
 they are not a word */
void	manage_input(t_shell *p)
{
	t_lst		*current_node;
	t_lst		*start_node;
	int			arg_count;
	int			i;

	current_node = p->token_list;
	while (current_node != NULL)
	{
		if (current_node->token == WORD || current_node->token == SQUOTE || current_node->token == DQUOTE)
		{
			start_node = current_node;
			arg_count = get_arg_count(start_node);
			start_node->args = malloc(sizeof(char *) * (arg_count + 1));
			if (!start_node->args)
			{
				perror("Failed to allocate memory for args");
				exit(EXIT_FAILURE);
			}
			i = 0;
			while (current_node != NULL && current_node->token != PIPE)
			{
				if (current_node->type == CMD || current_node->type == ARG)
				{
					start_node->args[i] = ft_strdup(current_node->content);
					if (i > 0)
						current_node->remove = true;
					i++;
				}
				current_node = current_node->next;
			}
			start_node->args[i] = NULL;
		}
		else
			current_node = current_node->next;
	}
}
