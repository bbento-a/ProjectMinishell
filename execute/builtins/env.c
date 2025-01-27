/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:39 by mde-maga          #+#    #+#             */
/*   Updated: 2025/01/27 11:10:15 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ms_env(t_env *env)
{
    while (env)
    {
        if (ft_strchr(env->value, '=') != NULL) // Check if '=' exists in the string
        {
            ft_putstr_fd(env->value, STDOUT);  // Print the variable
            ft_putstr_fd("\n", STDOUT);
        }
        env = env->next; // Move to the next node
    }
}

/* t_env	*create_env_node(char *value)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->value = strdup(value); // Duplicate the value string
    node->next = NULL;
    return (node);
}

// Add a node to the end of the linked list
void	add_env_node(t_env **head, char *value)
{
    t_env *new_node = create_env_node(value);
    if (!new_node)
        return;
    if (!*head)
        *head = new_node;
    else
    {
        t_env *temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

// Main function
int	main(void)
{
    t_env *env_list = NULL;

    // Create sample environment variables
    add_env_node(&env_list, "PATH=/usr/bin:/bin");
    add_env_node(&env_list, "USER=root");
    add_env_node(&env_list, "HOME=/root");
    add_env_node(&env_list, "NO_EQUALS_SIGN");

    // Call ms_env to print environment variables
    ms_env(env_list);

    // Free the list
    while (env_list)
    {
        t_env *temp = env_list;
        env_list = env_list->next;
        free(temp->value);
        free(temp);
    }

    return 0;
}

// Helper function implementations
char	*ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    return (c == '\0' ? (char *)s : NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
    if (s)
        write(fd, s, strlen(s));
} */