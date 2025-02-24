
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

void	clear_memory(t_command *cmds)
{
	t_command 	*temp;
	t_files		*tmp;

	while (cmds)
	{
		if (cmds->args)
			free_array(cmds->args);
		if (cmds->files)
		{
			tmp = cmds->files;
			while (tmp)
			{
				if (tmp->type == E_HERDOC)
					close (tmp->fd);
				free(tmp->file_name);
				free(tmp);
				tmp = tmp->next;
			}
		}
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
