
#include "../minishell.h"

// t_builtin	*init_builtins_list(void)
// {
// 	t_builtin	*builtin_list;

// 	builtin_list = malloc(sizeof(t_builtin) * 8);
// 	if (!builtin_list)
// 		return (NULL);
// 	builtin_list[0].name = ft_strdup("echo");
// 	builtin_list[0].func = builtin_echo;
// 	builtin_list[1].name = ft_strdup("cd");
// 	builtin_list[1].func = builtin_cd;
// 	builtin_list[2].name = ft_strdup("pwd");
// 	builtin_list[2].func = builtin_pwd;
// 	builtin_list[3].name = ft_strdup("env");
// 	builtin_list[3].func = builtin_env;
// 	builtin_list[4].name = ft_strdup("exit");
// 	builtin_list[4].func = builtin_exit;
// 	builtin_list[5].name = ft_strdup("export");
// 	builtin_list[5].func = builtin_export;
// 	builtin_list[6].name = ft_strdup("unset");
// 	builtin_list[6].func = builtin_unset;
// 	builtin_list[7].name = NULL;
// 	builtin_list[7].func = NULL;
// 	return (builtin_list);
// }

// Initiates the variables so we're not working wiith uninitialized values

void	init_data(char **envp)
{
	data()->env = envp;
	data()->prompt_flag = true;
	data()->prompt = NULL;
	data()->cmds = NULL;
	data()->error_parse = false;
	data()->exit_code = 0;
	data()->last_exit_status = 0;
	// data()->builtin_list = init_builtins_list();
	// if (!data()->builtin_list)
	// 	display_err(NULL, NULL, "Failed to allocate builtin list", 1);
}

// Stores data that will be needed to identify things for the parsing

t_minishell	*data(void)
{
	static t_minishell	data;

	return (&data);
}
