
#include "../../inc/minishell.h"

// Prints an error message to the stderr and takes/returns its error code

int	display_err(char *local, char *arg, char *error_msg, int err_code)
{
	if (local)
		printf("%s: ", local);
	if (arg)
		printf("%s: ", arg);
	printf("%s", error_msg);
	printf("\n");
	data()->exit_code = err_code;
	if (err_code < 0)
		data()->exit_code = 1;
	return (err_code);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->value);
		env->envp = NULL;
		tmp = env;
		env = env->next;
		free(tmp);
	}
	env = NULL;
}

void	clear_cmd_files(t_files **files)
{
	t_files	*tmp;

	if (!files || !*files)
		return ;
	while (*files)
	{
		if ((*files)->type == E_HERDOC && (*files)->fd > 2)
			close((*files)->fd);
		free((*files)->file_name);
		(*files)->file_name = NULL;
		tmp = *files;
		*files = (*files)->next;
		free(tmp);
	}
	files = NULL;
}

void	clear_memory(t_command *cmds)
{
	t_command 	*temp;

	while (cmds)
	{
		if (cmds->args)
			free_array(cmds->args);
		clear_cmd_files(&cmds->files);
		temp = cmds;
		cmds = cmds->next;
		free(temp);
	}
	cmds = NULL;
}

void	clear_fork(char *path, char **env_array)
{
	free(path);
	free_array(env_array);
	clear_memory(data()->cmds);
	clear_env(data()->env);
}
