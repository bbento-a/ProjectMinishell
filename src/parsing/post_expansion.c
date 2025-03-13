
#include "../../inc/minishell.h"

// Creates a node with the splitted content

static int	create_small_node(t_line **lst, char *str, int bgn, int len)
{
	t_line	*node;
	t_line	*last_node;

	node = my_malloc(sizeof(t_line));
	if (!node)
		return (display_err(NULL, NULL,
				"Error while allocating new node", 1));
	node->next = NULL;
	node->content = ft_substr(str, bgn, len);
	node->type_n = E_OTHER;
	node->type_q = '0';
	node->white_space = true;
	if (!(*lst))
	{
		node->prev = NULL;
		*lst = node;
	}
	else
	{
		last_node = find_lastnode(*lst);
		last_node->next = node;
		node->prev = last_node;
	}
	return (0);
}
// Splits characters separated by white spaces and passes the value
// of those isolated characters to a function to create nodes

t_line	*split_node(char *str)
{
	t_line	*add_lst;
	int		i;
	int		j;

	i = 0;
	add_lst = NULL;
	while (str[i])
	{
		j = 0;
		while (symbol_cmp(" \n\v\t", str[i]))
			i++;
		while (str[i + j] && !symbol_cmp(" \n\v\t", str[i + j]))
			j++;
		if (create_small_node(&add_lst, str, i, j))
			return (NULL);
		i += j;
	}
	return (add_lst);
}
// If a new list of tokens is created after the split, the token
// that had an old value of the expansion will be erased, and replaced
// by the new list

void	aux_erase_node(t_line *tmp, t_line *prompt, t_line *last, t_line *nl)
{
	while (tmp != prompt)
		tmp = tmp->next;
	if (tmp == prompt)
	{
		nl->prev = tmp->prev;
		tmp->prev->next = nl;
		last->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = last;
		nl->white_space = tmp->white_space;
	}
	free(tmp->content);
	free(tmp);
}

void	erase_lst_node(t_line **head, t_line *prompt, t_line *new_lst)
{
	t_line	*last_node;
	t_line	*tmp;

	tmp = *head;
	last_node = find_lastnode(new_lst);
	if (!prompt->prev)
	{
		*head = new_lst;
		if ((tmp)->next)
		{
			last_node->next = tmp->next;
			tmp->next->prev = last_node;
		}
		free(tmp->content);
		free(tmp);
	}
	else
		aux_erase_node(tmp, prompt, last_node, new_lst);
}

// This function will take the result of expansions and split it, if needed.
// The split will only happen if the expansion result has white spaces, and it
// once splitted, the result will be added to the token list

int	handle_post_expansion(t_line **input, t_line *prompt)
{
	t_line	*new_lst;
	int		i;

	i = 0;
	new_lst = NULL;
	while (prompt->content[i])
	{
		if (symbol_cmp(" \n\t", prompt->content[i]))
		{
			new_lst = split_node(prompt->content);
			if (!new_lst)
				return (1);
			break ;
		}
		i++;
	}
	if (new_lst)
		erase_lst_node(input, prompt, new_lst);
	return (0);
}
