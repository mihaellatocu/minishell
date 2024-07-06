/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:41:44 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/06 15:58:27 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Move to a new line and redisplay the prompt
Clear the input line
Move the cursor to a new line
Redisplay the prompt*/
void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_child_handler(int signum)
{
	if (signum)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

// Do nothing
void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

// Handle ctrl-D (EOF) to exit the shell
void	handle_eof(void)
{
	printf("exit\n");
	exit(0);
}
