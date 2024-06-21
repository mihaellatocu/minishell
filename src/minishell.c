/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:23:58 by mtocu             #+#    #+#             */
/*   Updated: 2024/06/19 15:44:57 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*This function return the operator that is found*/
// static t_token find_token(char *str, size_t *i)
// {
// 	if(str[*i] == '|')
// 		return(PIPE);
// 	else if(str[*i] == '<' && str[*i + 1] == '<')
// 	{
// 		(*i)++;
// 		return(DLESS);
// 	}
// 	else if(str[*i] == '<')
// 		return (LESS);
// 	else if (str[*i] == '>' && str[*i + 1] == '>')
// 	{
// 		(*i)++;
// 		return (DGREAT);
// 	}
// 	else
// 		return (GREAT);
// }

// static bool operator(int c)
// {
// 	if (c == PIPE || c == LESS || c == DLESS || c == DGREAT || c == '&' ||
// 		c == GREAT)
// 		return (true);
// 	return (false);
// }

// char *find_word(char *line, size_t *i, t_token token)
// {
// 	char *word;
// 	size_t start;
// 	size_t index;

// 	start = *i;
// 	index = 0;
// 	if ((char)token == WORD)
// 		while (!ft_isspace((int)line[*i]) && !operator((int)line[*i]) && line[*i] != '\0')
// 			(*i)++;
// 	else
// 	{
// 		start++;
// 		while(line[++(*i) != (char)token])
// 			;
// 	}
// 	word = malloc((char)(*i - start + 2) * sizeof(char));
// 	// if (!word) // to be added
// 	// 	error(1);
// 	// printf("%zu ", start);
// 	while (start < *i)
// 		word[index++] = line[start++];
// 	word[index] = '\0';
// 	 if (token == WORD)
// 	 	(*i)--;

// 	//printf("word from word function   %s\n", word);
// 	return (word);
// }

// t_lst  *split_into_tokens(char *line, t_shell *p) //split the line in words and tokens, wc -l | ls -> 4 tokens
// {
// 	size_t i;
// 	int length;

// 	i = -1;
// 	length = ft_strlen(line);
// 	while (++i < length)
// 	{
// 		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
// 			lstadd_back(&p->token_list, lstnew(NULL, find_token(line, &i)));
		
// 		else if (line[i] == '\'')
// 			lstadd_back(&p->token_list, lstnew(NULL, SQUOTE));
// 		else if (line[i] == '\"')
// 			lstadd_back(&p->token_list, lstnew(NULL, DQUOTE));
// 		else if(ft_isalnum(line[i]) || line[i] == '-' || line[i] == '.' || line[i] == '=' ||
// 			line[i] == '/' || line[i] == '$' || line[i] == '*')
// 			lstadd_back(&p->token_list, lstnew(find_word(line, &i, WORD), WORD));
// 		//printf("%zu\n", i);
// 	}	
// 	return (p->token_list);
// }

// int	get_arg_count(t_lst *node)
// {
// 	int	count;

// 	count = 0;
// 	while(node != NULL && node->token != PIPE)
// 	{
// 		if (node->type == CMD || node->type == ARG)
// 			count++;
// 		node = node->next;
// 	}
// 	return (count);
// }

// void	manage_input(t_shell *p) // create a list of arguments on each node , and move the tokens node if they are not a word
// {
// 	t_lst		*current_node;
// 	t_lst		*start_node;
// 	int			arg_count;
// 	int			i;
	
// 	current_node = p->token_list; // inceputul listei
// 	while (current_node != NULL) 
// 	{

// 		if (current_node->token == WORD)
// 		{
// 			start_node = current_node;
// 			arg_count = get_arg_count(start_node);
// 			// printf("nr de args:    %d\n", arg_count);

// 			start_node->args = malloc(sizeof(char *) * (arg_count + 1));
// 			if (!start_node->args)
// 			{
// 				perror("Failed to allocate memory for args");
// 				exit(EXIT_FAILURE);
// 			}
// 			i = 0;
						
// 			while(current_node != NULL && current_node->token != PIPE)
// 			{
// 				if (current_node->type == CMD || current_node->type == ARG)
// 				{
// 					start_node->args[i] = ft_strdup(current_node->content);
// 					 //printf("node   %s\n", start_node->args[i]);
// 					if (i > 0)
// 						current_node->remove = true;
// 					i++;
// 				}
// 				current_node = current_node->next;
// 			}
// 			start_node->args[i] = NULL;
// 		}	
// 		else
// 			current_node = current_node->next;
// 	}
// }

int main(int argc, char **argv, char **envp)
{
	t_shell p;
	char *line;

	init(&p, envp, argc, argv);
	setup_signal_handlers();
	while(1)
	{
		line = readline("minishell>> ");
		if (line == NULL)
		{
			//ft_putstr_fd("ex\n", STDOUT_FILENO);
			;//break ;
			handle_eof();
		}
		add_history(line);
		p.token_list = split_into_tokens(line, &p);
		
		set_command_structure(p.token_list, false); // divide the input to operations cmd and ar
		
		find_redirections(p.token_list);
		cleaning_args(&p.token_list); // use after find redirection is enabled
		
		manage_input(&p);// separate CMD from ARGs and remove the nodes from ARGs
		cleaning_args(&p.token_list);

		print_list_cmd(p.token_list);
		
		free_allocation_malloc(&p.token_list, line);
		//print_env(p.envir);
	   }
	free_allocation_malloc_env(&p.envir);
	free(line);
	
	return (0);
}
