/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute9_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:34:31 by mtocu             #+#    #+#             */
/*   Updated: 2024/07/11 14:50:49 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outfile(t_lst *cmd)
{
	t_file	*current;

	if (cmd->outfile == NULL)
		return (1);
	current = cmd->outfile;
	while (current != NULL)
	{
		if (current->token == GREAT)
			cmd->fd_out = open(current->name, \
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (current->token == DGREAT)
			cmd->fd_out = open (current->name, \
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (cmd->fd_out < 0)
		{
			cmd->run = false;
			return (perror(current->name), -1);
		}
		current = current->next;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == '\n' && s2[i] == '\0')
			return (0);
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2 [i]);
		i++;
	}
	return (0);
}

/*This function is called if << redirection is used, it reads from terminal*/
void	read_from_terminal(t_lst *cmd, int fd_in, char *delimiter)
{
	int		check;
	int		buffer;
	char	buffer_size[1024];

	check = 1;
	while (check != 0)
	{
		write (1, "> ", 2);
		buffer = read(0, buffer_size, 1024);
		buffer_size[buffer] = '\0';
		check = ft_strcmp(buffer_size, delimiter);
		if (check != 0)
			write (fd_in, buffer_size, buffer);
	}
	close(fd_in);
	cmd->fd_in = open(".here_doc", O_RDWR | O_CREAT, 0666);
}

int	infile(t_lst *cmd)
{
	t_file	*current;

	if (cmd->infile == NULL)
		return (0);
	current = cmd->infile;
	while (current != NULL)
	{
		if (current->token == LESS)
			cmd->fd_in = open(current->name, O_RDONLY);
		else if (current->token == DLESS)
			cmd->fd_in = open(".here_doc", O_RDWR | O_CREAT, 0666);
		if (cmd->fd_in == -1)
		{
			cmd->run = false;
			return (perror(current->name), 1);
		}
		if (current->token == DLESS)
			read_from_terminal(cmd, cmd->fd_in, current->name);
		current = current->next;
	}
	return (0);
}
