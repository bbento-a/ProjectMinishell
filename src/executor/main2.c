// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/10 18:23:41 by mde-maga          #+#    #+#             */
// /*   Updated: 2025/02/21 15:25:33 by bbento-a         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../inc/minishell.h"

// t_sig g_sig = {0};
// t_token *token_parser(char *line)
// {
//     t_token *head = NULL, *current = NULL;
//     char *token_str;
//     char *delim = " \t|><";
//     char *line_copy = strdup(line);
//     char *saveptr;

//     token_str = strtok_r(line_copy, delim, &saveptr);
//     while (token_str)
//     {
//         t_token *new_token = malloc(sizeof(t_token));
//         if (!new_token)
//             return NULL;

//         // Allocate a fresh copy so we don't rely on line_copy memory
//         new_token->str = strdup(token_str);
//         if (!new_token->str) {
//             free(new_token);
//             break;
//         }

//         new_token->type = CMD;
//         new_token->next = NULL;

//         if (!head) {
//             head = new_token;
//             current = head;
//         } else {
//             current->next = new_token;
//             current = new_token;
//         }

//         token_str = strtok_r(NULL, delim, &saveptr);
//     }
//     free(line_copy); // Safe to free now
//     return head;
// }

/// Removed t_mini *mini as a param, and now this function returns
/// a pointer to the beginning of env list

t_env *parse_envp(char **envp)
{
    t_env *new_env;
    t_env *tmp;
    int i = 0;

    while (envp[i])
    {
        new_env = malloc(sizeof(t_env));
        new_env->value = strdup(envp[i]);
        new_env->envp = &envp[i];
        new_env->next = tmp;
        tmp = new_env;
        i++;
    }
	return (tmp);
}


// void handle_signal(int sig)
// {
//     if (sig == SIGINT)
//     {
//         ft_putstr_fd("\n", STDOUT);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;

//     t_mini *mini;
//     t_token *tokens;
//     char *line;
//     char **cmd;
//     int result;

//     // Handle SIGINT (Ctrl + C) signal
//     signal(SIGINT, handle_signal);

//     // Initialize the mini shell struct
//     mini = malloc(sizeof(t_mini));
//     if (!mini)
//         return (1);
//     mini->env = NULL;  // This will be populated from envp
//     mini->ret = 0;
//     mini->charge = 1;

//     // Parse the environment variables into t_env linked list
//     parse_envp(envp, mini);  // This function populates mini->env

//     // Start the shell prompt loop
//     while (1)
//     {
//         line = readline("minishell> ");  // Read user input

//         if (!line)
//         {
//             ft_putstr_fd("\n", STDOUT);
//             break;
//         }

//         if (line && *line)
//         {
//             add_history(line);  // Add the command to history

//             // Tokenize the input into commands
//             tokens = token_parser(line);  // Tokenize the line into a list of tokens

//             // Check if the command is built-in
//             cmd = cmd_tab(tokens);  // Convert tokens to command args
//             if (is_builtin(cmd[0])) 
//             {
//                 result = exec_builtin(cmd, mini);  // Execute built-in command
//                 mini->ret = result;  // Store return status
//             }
//             else 
//             {
//                 exec_cmd(mini, tokens);  // Execute non-built-in commands (external binaries)
//             }

//             free_tab(cmd);  // Free the cmd array
//             free_token(tokens);  // Free the token list
//         }

//         free(line);  // Free the input line after processing
//     }

//     // Cleanup and exit
//     free(mini);  // Free the mini struct
//     return (0);
// }

