#include "minishell.h"



int	handle_echo_cmd(t_shell *p, t_lst *cmd)
{
	int i;
	(void)p;

	i = 1;
	if (!cmd->args[i])
		printf("\n");
	else
	{
		if (ft_strncmp(cmd->args[i], "-n", 3) == 0)
			i++;
		while (cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			i++;
			if (cmd->args[i])
				printf(" ");
		}
	}
	if (ft_strncmp(cmd->args[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}