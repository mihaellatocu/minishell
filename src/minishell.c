/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:23:58 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/06 15:07:14 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			//ft_putstr_fd("ex\n", STDOUT_FILENO);
			;//break ;
			handle_eof();
		}
		add_history(line);
		p.token_list = split_into_tokens(line, &p);

		find_dollar_sign_and_replace(&p);
		//print_list(p.token_list);
		
		set_command_structure(p.token_list, false); // divide the input to operations cmd and ar
		
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
