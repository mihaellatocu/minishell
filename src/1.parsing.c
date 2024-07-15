/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:20:04 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 14:46:29 by mtocu            ###   ########.fr       */
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
			lstadd_back(&p->token_list, \
				lstnew(find_word(line, &i, SQUOTE), SQUOTE));
		else if (line[i] == '\"')
			lstadd_back(&p->token_list, \
				lstnew(find_word(line, &i, DQUOTE), DQUOTE));
		else if (ft_isalnum(line[i]) || line[i] == '-' || line[i] == '.'
			|| line[i] == '=' || line[i] == '/' || line[i] == '$'
			|| line[i] == '*' || line[i] == '_' || line[i] == '+')
			lstadd_back(&p->token_list, \
				lstnew(find_word(line, &i, WORD), WORD));
	}
	p->error = false;
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

static void	add_arg_to_cmd(t_lst *start_node, t_lst *current, int *i)
{
	if (current->type == CMD || current->type == ARG)
	{
		start_node->args[*i] = ft_strdup(current->content);
		if (*i > 0)
			current->remove = true;
		(*i)++;
	}
}

/* create a list of arguments on each node , and move the tokens node if
 they are not a word */
void	manage_input(t_shell *p, int i, int arg_count)
{
	t_lst		*current;
	t_lst		*start_node;

	current = p->token_list;
	while (current != NULL)
	{
		if (current->token == WORD || current->token == SQUOTE
			|| current->token == DQUOTE)
		{
			start_node = current;
			arg_count = get_arg_count(start_node);
			start_node->args = malloc(sizeof(char *) * (arg_count + 1));
			if (!start_node->args)
				exit(EXIT_FAILURE);
			i = 0;
			while (current != NULL && current->token != PIPE)
			{
				add_arg_to_cmd(start_node, current, &i);
				current = current->next;
			}
			start_node->args[i] = NULL;
		}
		else
			current = current->next;
	}
}
