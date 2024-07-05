/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:46:47 by antestem          #+#    #+#             */
/*   Updated: 2024/07/05 16:12:50 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
    (void)sig;
    // Move to a new line and redisplay the prompt
    rl_replace_line("", 0);  // Clear the input line
    printf("\n");
	rl_on_new_line();      // Move the cursor to a new line
    rl_redisplay();          // Redisplay the prompt
}

void handle_sigquit(int sig)
{
    (void)sig;
    // Do nothing
}

void setup_signal_handlers(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

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

void handle_eof(void)
{
    // Handle ctrl-D (EOF) to exit the shell
    printf("exit\n");
    exit(0);
}
