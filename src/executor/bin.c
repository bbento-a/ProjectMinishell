/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/24 13:24:50 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int error_message(char *path)
{
    DIR *folder;
    int fd;
    int ret;

    if (!path)
    {
        ft_putendl_fd("minishell: NULL path provided", STDERR);
        return (ERROR);
    }
    fd = open(path, O_WRONLY);
    folder = opendir(path);
    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(path, STDERR);
    ret = handle_error(path, folder, fd);
    if (folder)
        closedir(folder);
    if (fd != -1)
        close(fd);
    return (ret);
}

///Removed mini
///Removed the g_sig global struct for signals and changed its pid to int
///Signals now will be caught with WIFSIGNALED()

int magic_box(char *path, char **args, t_env *env)
{
    char **env_array;
    char *ptr;
	int	pid;
    int ret = ERROR;  // Initialize ret with a default value

    if (!path || !args)
    {
        ft_putendl_fd("minishell: Invalid arguments provided to magic_box", STDERR);
        return (ERROR);
    }

	pid = fork();
    if (pid == 0)
    {
        ptr = env_to_str(env);
        if (!ptr)
            exit(ERROR);
        env_array = ft_split(ptr, '\n');
		// ft_printmtx(env_array);
        free(ptr);

        if (env_array)
        {
            if (ft_strchr(path, '/') != NULL)
            {
                execve(path, args, env_array);
                // If execve fails, we will return the error from error_message
                ret = error_message(path);
            }
            else
                ret = error_message(path);
        }

        free_tab(env_array);
        exit(ret);  // Now, ret will always have a value when passed to exit()
    }

    waitpid(pid, &ret, 0);

    if (WIFSIGNALED(ret)) /// if the process gets terminated by a signal, it returns the value of that signal
    {
        return (WIFSIGNALED(ret));
    }

    if (WIFEXITED(ret))
    {
        return (WEXITSTATUS(ret));
    }
    else
    {
        return ERROR;
    }
}

char *path_join(const char *s1, const char *s2)
{
    char *tmp;
    char *path;

    if (!s1 || !s2)
        return (NULL);
    tmp = ft_strjoin(s1, "/");
    if (!tmp)
        return (NULL);
    path = ft_strjoin(tmp, s2);
    free(tmp);
    return (path);
}

char *check_dir(char *bin, char *command)
{
    DIR *folder;
    struct dirent *item;
    char *path;

    if (!bin || !command)
        return (NULL);
    folder = opendir(bin);
    if (!folder)
        return (NULL);
    path = NULL;
    while ((item = readdir(folder)))
    {
        if (ft_strncmp(item->d_name, command, ft_strlen(item->d_name)) == 0)
        {
            path = path_join(bin, item->d_name);
            break;
        }
    }
    closedir(folder);
    return (path);
}

/// Added a tmp to iterate env so the original doesn't get modified

int exec_bin(char **args, t_env *env)
{
    int i;
    char **bin;
    char *path;
    int ret;
	t_env	*tmp;
	
	tmp = env;
    if (!args || !args[0])
        return (ERROR);
    while (tmp && tmp->value && ft_strncmp(tmp->value, "PATH=", 5) != 0)
        tmp = tmp->next;
    if (!tmp || !tmp->value)
        return (magic_box(args[0], args, env));
    bin = ft_split(tmp->value + 5, ':');
    if (!bin)
        return (ERROR);
    i = 0;
    path = check_dir(bin[i], args[0]);
    while (!path && bin[++i])
        path = check_dir(bin[i], args[0]);
    if (path)
    {
		ret = magic_box(path, args, env);
	}
    else
        ret = magic_box(args[0], args, env);
    free_tab(bin);
    free(path);
    return (ret);
}
