/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:23:58 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/09 15:06:12 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    insert_cmd_node_before(t_lst *node)
{
    t_lst   *new_node;
    if (node == NULL)
        return ;
    new_node = lstnew(ft_strdup("true"), WORD);
    if (new_node == NULL)
        return ;//ft_malloc_error();  error to add
    new_node->type = CMD;
    new_node->run = false;
    new_node->prev = node->prev;
    new_node->next = node;
    if (node->prev != NULL)
        node->prev->next = new_node;
    node->prev = new_node;
}
// Function to insert a CMD type node after the specified node
void    insert_cmd_node_after(t_lst *node)
{
    t_lst   *new_node;
    if (node == NULL)
        return ;
    new_node = lstnew(ft_strdup("true"), WORD);
    if (new_node == NULL)
        return ;//ft_malloc_error();  error to add
    new_node->type = CMD;
    new_node->run = false;
    node->next = new_node;
    new_node->prev = node;
    new_node->next = NULL;
}
// Function to ensure there is at least one CMD type between each pipe
void    ensure_cmd_between_pipes(t_lst *token_list)
{
    bool    is_a_cmd;
    t_lst   *current;
    current = token_list;
    is_a_cmd = false;
    while (current != NULL)
    {
        if (current->type == CMD)
            is_a_cmd = true;
        if (current->token == PIPE)
        {
            if (!is_a_cmd)
                insert_cmd_node_before(current);
            is_a_cmd = false;
        }
        else if (current->next == NULL)
        {
            if (!is_a_cmd)
                insert_cmd_node_after(current);
            is_a_cmd = false;
        }
        current = current->next;
    }
}


int main(int argc, char **argv, char **envp)
{
	t_shell p;

	char *line;
	init(&p, envp, argc, argv);
	setup_signal_handlers();
	while(p.run == true)
	{
		line = readline("minishell>> ");
		if (line == NULL)
			handle_eof();
		add_history(line);
		p.token_list = split_into_tokens(line, &p);

		find_dollar_sign_and_replace(&p);
		//print_list(p.token_list);
		
		set_command_structure(p.token_list, false); // divide the input to operations cmd and ar
		ensure_cmd_between_pipes(p.token_list); 
		find_redirections(p.token_list);
		cleaning_args(&p.token_list); // use after find redirection is enabled
		
		manage_input(&p);// separate CMD from ARGs and remove the nodes from ARGs
		
		cleaning_args(&p.token_list);

		// print_list_cmd(p.token_list);
		count_cmd(p.token_list); // removing pipes
		cleaning_args(&p.token_list);
		execute(&p);
		free_allocation_malloc(&p.token_list, line);
	}
	free_allocation_malloc_env(&p.envir);
	
	return (0);
}
