
#include "../inc/minishell.h"

void	free_files(t_files *files)
{
	t_files	*tmp;

	if (!files)
		return ;
	while (files)
	{
		tmp = files;
		files = files->next;
		if (tmp->type == E_HERDOC && access(tmp->file_name, F_OK) == 0
			&& unlink(tmp->file_name) == -1)
			display_err(NULL, tmp->file_name, "Error removing heredoc file", 1);
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_cmds(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds)
		return ;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		if ((*cmds)->args)
			free((*cmds)->args);
		free_files((*cmds)->in_file);
		free_files((*cmds)->out_file);
		free(*cmds);
		*cmds = tmp;
	}
	cmds = NULL;
}

void	free_builtin_list(t_builtin *builtin_list)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		free(builtin_list[i].name);
		i++;
	}
	free(builtin_list);
}

// int	finish_environment(void)
// {
// 	// free_envp();
// 	free_builtin_list(data()->builtin_list);
// 	return (0);
// }

void	clear_memory(t_command **commands)
{
	free_cmds(commands);
}
