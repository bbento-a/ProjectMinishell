/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:35:33 by bbento-a          #+#    #+#             */
/*   Updated: 2024/07/06 15:08:33 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*tmp;
	t_list	*reslst;

	reslst = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst != NULL)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_lstclear(&reslst);
			return (NULL);
		}
		ft_lstadd_back(&reslst, tmp);
		lst = lst->next;
	}
	return (reslst);
}
