/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:09:00 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/17 16:01:05 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*expand_variable(char *str, t_env *env)
{
	t_env	*tmp;
	size_t	len;

	if (!str || str[0] != '$' || str[1] == '\0')
		return (str);
	if (str[1] == '?')
	{
		free(str);
		return (ft_itoa(g_sig.exit_status));
	}
	str++;
	len = ft_strlen(str);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, str, len) == 0 && tmp->value[len] == '=')
		{
			free(str - 1);
			return (ft_strdup(tmp->value + len + 1));
		}
		tmp = tmp->next;
	}
	return (str - 1);
}

char	*expansions(char *cmd, t_env *env, int ret)
{
	(void)ret;
	if (!cmd)
		return (NULL);
	return (expand_variable(ft_strdup(cmd), env));
}

/* Checks if the token list contains a pipe (|) */
int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

/* Closes a file descriptor safely */
void	ft_close(int fd)
{
    if (fd >= 0 && fcntl(fd, F_GETFD) != -1)
        close(fd);
}

/* Handles the built-in exit command */
void	mini_exit(t_mini *mini, char **cmd)
{
	int	exit_code;

	exit_code = mini->ret;
	if (cmd[1])
	{
		if (ft_isdigit(cmd[1][0]))
			exit_code = ft_atoi(cmd[1]);
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", STDERR);
			exit_code = 255;
		}
	}
	free_tab(cmd);
	free_token(mini->start);
	ft_putstr_fd("exit\n", STDOUT);
	exit(exit_code);
}