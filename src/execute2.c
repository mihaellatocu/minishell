#include "minishell.h"

/*Check if it's only one command and if that command is built in*/
bool	is_only_one_cmd(t_lst *node)
{
	bool	is_build_in;

	is_build_in = false;
	if (ft_strncmp(node->args[0], "cd", 3) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "pwd", 4) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "env", 4) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "export", 7) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "unset", 6) == 0)
		is_build_in = true;
	if (ft_strncmp (node->args[0], "echo", 5) == 0)
		is_build_in = true;
	if (ft_strncmp(node->args[0], "exit", 5) == 0)
		is_build_in = true;
	return (is_build_in);
}

int		handle_build_in(t_shell *p, t_lst *command)
{
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		return (handle_cd_cmd(p, command));
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		return (handle_pwd_cmd(p, command));
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		return (handle_exit_cmd(p, command));
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		return (handle_env_cmd(p, command));
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		return (handle_unset_cmd(p, command));
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		return (handle_export_cmd(p, command));
	if	(ft_strncmp(command->args[0], "echo", 5) == 0)
		return (handle_echo_cmd(p, command));
	return (0);
}