#include "minishell.h"


char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	int		i;
	char	*part_p_with_slash;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_p_with_slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_p_with_slash, cmd);
		free(part_p_with_slash);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_error("The command is not valid");
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

void	initiate(t_state *p, int argc, char **argv, char **envp)
{
	p->argv = argv;
	p->argc = argc;
	p->envp = envp;
}

// void	ft_error(const char *message)
// {
// 	perror(message);
// 	exit(EXIT_FAILURE);
// }

// void	validate_args(t_context *p)
// {
// 	if (p->argc < 5)
// 		ft_error("Too few arguments");
// 	p->filein = open(p->argv[1], O_RDONLY);
// 	if (access(p->argv[1], R_OK) == -1)
// 		ft_error("I can't access the first file");
// 	if (p->filein == -1)
// 		ft_error("The first file cannot be accessed");
// 	p->fileout = open(p->argv[p->argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
// 	if (access(p->argv[p->argc - 1], W_OK) == -1)
// 		ft_error("The second file cannot be accessed");
// 	if (p->fileout == -1)
// 		ft_error("The second file cannot be accessed");
// }

void	child_process2(t_shell *p, int i, int *fd, int prev_fd)
{
	while (++i <= p->argc - 2)
	{
		if (pipe(fd) == -1)
			ft_error("pipe");
		p->pid = fork();
		if (p->pid == -1)
			ft_error("fork");
		if (p->pid == 0)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
			if (i != p->argc - 2)
				dup2(fd[1], STDOUT_FILENO);
			else
				dup2(p->fileout, STDOUT_FILENO);
			close(fd[0]);
			execute(p->argv[i], p->envp);
		}
		close(fd[1]);
		prev_fd = fd[0];
	}
}

// int	main(int argc, char *argv[], char **envp)
// {
// 	t_context	p;

// 	initiate(&p, argc, argv, envp);
// 	validate_args(&p);
// 	p.prev_fd = p.filein;
// 	child_process2(&p, 1, p.fd, p.prev_fd);
// 	waitpid(p.pid, NULL, 0);
// 	close(p.filein);
// 	close(p.fileout);
// 	return (0);
// }