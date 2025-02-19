/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/19 16:42:50 by bbento-a         ###   ########.fr       */
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

int magic_box(char *path, char **args, t_env *env, t_mini *mini)
{
    char **env_array;
    char *ptr;
    int ret = ERROR;  // Initialize ret with a default value

    if (!path || !args)
    {
        ft_putendl_fd("minishell: Invalid arguments provided to magic_box", STDERR);
        return (ERROR);
    }

    g_sig.pid = fork();
    if (g_sig.pid == 0)
    {
        ptr = env_to_str(env);
        if (!ptr)
            exit(ERROR);

        env_array = ft_split(ptr, '\n');
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
        free_token(mini->start);
        exit(ret);  // Now, ret will always have a value when passed to exit()
    }

    waitpid(g_sig.pid, &ret, 0);

    if (g_sig.sigint == 1 || g_sig.sigquit == 1)
    {
        return (g_sig.exit_status);
    }

    if (WIFEXITED(ret))
    {
        return WEXITSTATUS(ret);
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
        if (ft_strcmp(item->d_name, command) == 0)
        {
            path = path_join(bin, item->d_name);
            break;
        }
    }
    closedir(folder);
    return (path);
}

int exec_bin(char **args, t_env *env, t_mini *mini)
{
    int i;
    char **bin;
    char *path;
    int ret;

    if (!args || !args[0])
        return (ERROR);
    while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
        env = env->next;
    if (!env || !env->value)
        return (magic_box(args[0], args, env, mini));
    bin = ft_split(env->value + 5, ':');
    if (!bin)
        return (ERROR);
    i = 0;
    path = check_dir(bin[i], args[0]);
    while (!path && bin[++i])
        path = check_dir(bin[i], args[0]);
    if (path)
        ret = magic_box(path, args, env, mini);
    else
        ret = magic_box(args[0], args, env, mini);
    free_tab(bin);
    free(path);
    return (ret);
}
