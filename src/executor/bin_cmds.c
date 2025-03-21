/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/21 16:53:29 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	if (!s1 || !s2)
		return (NULL);
	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	if (!bin || !command)
		return (NULL);
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strncmp(item->d_name, command, ft_strlen(item->d_name)) == 0)
		{
			path = path_join(bin, command);
			break ;
		}
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

static char	*find_bin_path(t_command *cmd, char **bin)
{
	int		i;
	char	*path;

	i = 0;
	path = check_dir(bin[i], cmd->args[0]);
	while (!path && bin[++i])
		path = check_dir(bin[i], cmd->args[0]);
	free_array(bin);
	return (path);
}

int	exec_bin(t_command *cmd, t_env *env)
{
	char	**bin;
	char	*path;
	int		ret;
	t_env	*tmp;

	tmp = env;
	ret = 0;
	if (!cmd->args || !cmd->args[0])
		return (data()->exit_code);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		return (launch_process(ft_strdup(cmd->args[0]), cmd, env));
	while (tmp && tmp->value && ft_strncmp(tmp->value, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (launch_process(ft_strdup(cmd->args[0]), cmd, env));
	bin = ft_split(tmp->value + 5, ':');
	if (!bin)
		return (display_err(NULL, NULL, "Failed to create bin", 1));
	path = find_bin_path(cmd, bin);
	if (path)
		ret = launch_process(path, cmd, env);
	else
		ret = launch_process(ft_strdup(cmd->args[0]), cmd, env);
	return (ret);
}
