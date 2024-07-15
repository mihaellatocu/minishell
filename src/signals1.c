/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:41:44 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 13:36:06 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Move to a new line and redisplay the prompt */
void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

/* SIGINT handler for child processes */
void	sigint_child_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

/* SIGQUIT handler for child processes */
void	sigquit_child_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		exit(131);
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
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

void	setup_child_signal_handlers(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigquit_child_handler);
}
