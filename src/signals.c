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

/* Move to a new line and redisplay the prompt */
void handle_sigint(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

/* Handle SIGQUIT (ctrl + \) */
void handle_sigquit(int sig)
{
    (void)sig;
    if (rl_line_buffer[0] == '\0')
    {
        // If the prompt is empty, do nothing
        rl_on_new_line();
        rl_redisplay();
    }
    else
    {
        // If there is input, quit the shell
        rl_replace_line("", 0);
        rl_redisplay();
        write(STDOUT_FILENO, "Quit\n", 5);
        exit(0);
    }
}

/* SIGINT handler for child processes */
void sigint_child_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        exit(130);  // 128 + SIGINT
    }
}

/* SIGQUIT handler for child processes */
void sigquit_child_handler(int signum)
{
    if (signum == SIGQUIT)
    {
        write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
        exit(131);  // 128 + SIGQUIT
    }
}

/* Handle ctrl-D (EOF) to exit the shell */
void handle_eof(void)
{
    write(STDOUT_FILENO, "exit\n", 5);
    exit(0);
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

void setup_child_signal_handlers(void)
{
    signal(SIGINT, sigint_child_handler);  // Use child-specific handler for SIGINT
    signal(SIGQUIT, sigquit_child_handler); // Use child-specific handler for SIGQUIT
}