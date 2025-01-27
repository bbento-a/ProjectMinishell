/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/01/24 15:33:04 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


int error_message(char *path)
{
    DIR *folder = NULL;
    int fd = -1;
    int ret;

    if (!path) {
        ft_putendl_fd("minishell: NULL path provided", STDERR);
        return (ERROR);
    }

    fd = open(path, O_WRONLY);
    folder = opendir(path);

    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(path, STDERR);

    if (ft_strchr(path, '/') == NULL)
        ft_putendl_fd(": command not found", STDERR);
    else if (fd == -1 && folder == NULL)
        ft_putendl_fd(": No such file or directory", STDERR);
    else if (fd == -1 && folder != NULL)
        ft_putendl_fd(": is a directory", STDERR);
    else if (fd != -1 && folder == NULL)
        ft_putendl_fd(": Permission denied", STDERR);

    if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
        ret = UNKNOWN_COMMAND;
    else
        ret = IS_DIRECTORY;

    if (folder)
        closedir(folder);
    if (fd != -1)
        close(fd);

    return (ret);
}

int magic_box(char *path, char **args, t_env *env, t_mini *mini)
{
    char **env_array = NULL;
    char *ptr = NULL;
    int ret;

    if (!path || !args) {
        ft_putendl_fd("minishell: Invalid arguments provided to magic_box", STDERR);
        return (ERROR);
    }

    g_sig.pid = fork();
    if (g_sig.pid == 0) {
        ptr = env_to_str(env);
        if (!ptr)
            exit(ERROR);

        env_array = ft_split(ptr, '\n');
        ft_memdel(ptr);

        if (env_array && ft_strchr(path, '/') != NULL)
            execve(path, args, env_array);

        ret = error_message(path);
        free_tab(env_array);
        free_token(mini->start);
        exit(ret);
    } else {
        waitpid(g_sig.pid, &ret, 0);
    }

    if (g_sig.sigint == 1 || g_sig.sigquit == 1)
        return (g_sig.exit_status);

    return (WIFEXITED(ret) ? WEXITSTATUS(ret) : ERROR);
}

char *path_join(const char *s1, const char *s2)
{
    char *tmp = NULL;
    char *path = NULL;

    if (!s1 || !s2)
        return (NULL);

    tmp = ft_strjoin(s1, "/");
    if (!tmp)
        return (NULL);

    path = ft_strjoin(tmp, s2);
    ft_memdel(tmp);

    return (path);
}

char *check_dir(char *bin, char *command)
{
    DIR *folder;
    struct dirent *item;
    char *path = NULL;

    if (!bin || !command)
        return (NULL);

    folder = opendir(bin);
    if (!folder)
        return (NULL);

    while ((item = readdir(folder))) {
        if (ft_strcmp(item->d_name, command) == 0) {
            path = path_join(bin, item->d_name);
            break;
        }
    }

    closedir(folder);
    return (path);
}

int exec_bin(char **args, t_env *env, t_mini *mini)
{
    int i = 0;
    char **bin;
    char *path = NULL;
    int ret = UNKNOWN_COMMAND;

    if (!args || !args[0])
        return (ERROR);

    while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
        env = env->next;

    if (!env || !env->value)
        return (magic_box(args[0], args, env, mini));

    bin = ft_split(env->value + 5, ':'); // Skip "PATH=" prefix
    if (!bin)
        return (ERROR);

    path = check_dir(bin[0], args[0]);
    while (!path && bin[++i])
        path = check_dir(bin[i], args[0]);

    if (path)
        ret = magic_box(path, args, env, mini);
    else
        ret = magic_box(args[0], args, env, mini);

    free_tab(bin);
    ft_memdel(path);

    return (ret);
}
