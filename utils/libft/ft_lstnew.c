/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:24:07 by mde-maga          #+#    #+#             */
/*   Updated: 2023/10/09 13:29:52 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head_list;

	head_list = (t_list *)malloc(sizeof(t_list));
	if (!head_list)
		return (NULL);
	head_list->content = content;
	head_list->next = NULL;
	return (head_list);
}
/* int main() 
{
    t_list *newNode = ft_lstnew("jonkler");
	
    if (newNode) 
	{
        printf("Content of the node: %s\n", (char *)newNode->content);

        free(newNode);
    } else 
	{
        printf("Failed to create a new node.\n");
    }

    return 0;
} */