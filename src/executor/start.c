/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:42:40 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/03 11:36:28 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
char **cmd_tab(t_token *start)
{
    t_token *token;
    char **tab;
    int i;

    if (!start)
        return (NULL);
    token = start->next;
    i = 2;
    while (token && token->type < TRUNC)
    {
        token = token->next;
        i++;
    }
    if (!(tab = malloc(sizeof(char *) * i)))
        return (NULL);
    token = start->next;
    tab[0] = start->str;
    i = 1;
    while (token && token->type < TRUNC)
    {
        tab[i++] = token->str;
        token = token->next;
    }
    tab[i] = NULL;
    return (tab);
}

int exec_cmd(t_command *command)
{
    char **cmd;
    int ret_val;

    cmd = command->args;
    if (cmd && is_builtin(cmd[0]))
        ret_val = exec_builtin(cmd);
    else if (cmd)
    {
        if (command->next) // If there's a next command, handle pipes
            ret_val = handle_pipes(command, data()->env);
        else
            ret_val = exec_bin(command, data()->env);
    }
    return (ret_val);
}