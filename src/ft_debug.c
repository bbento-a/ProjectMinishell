/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:40:35 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 10:34:48 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_printmtx(char **mtx)
{
	int	i;

	if (!mtx || !*mtx)
		return ;
	i = 0;
	while (mtx[i])
	{
		ft_printf("string %d:", i);
		ft_printf("%s«\n", mtx[i]);
		i++;
	}
}

void	ft_printlist(t_line *lst)
{
	t_line	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		ft_printf("\nnode %i:\n", i);
		ft_printf("content: %s«\n", tmp->content);
		ft_printf("type_q: %c\n", tmp->type_q);
		ft_printf("type_n: %d\n", tmp->type_n);
		ft_printf("has white space before?: %d\n", tmp->white_space);
		i++;
		tmp = tmp->next;
	}
}

void	print_filenodes(t_files *files)
{
	if (!files)
	{
		ft_printf("No in_files in command\n");
		return ;
	}
	while (files)
	{
		ft_printf("type of redir: %d\n", files->type);
		ft_printf("file name: %s\n", files->file_name);
		if (files->type == E_HERDOC)
			ft_printf("is delimiter in quotes?: %d\n", files->hq_limiter);
		files = files->next;
	}
}

void	ft_printfiles(t_files *files)
{
	t_files	*tmp;
	int		i;

	i = 0;
	tmp = files;
	while (tmp)
	{
		ft_printf("\nfile %i:\n", i);
		ft_printf("filename: %s«\n", tmp->file_name);
		i++;
		tmp = tmp->next;
	}
}

void	ft_print_env(t_env *env)
{
	ft_printf("Printing Env:\n");
	while (env)
	{
		ft_printf("%s\n", env->value);
		env = env->next;
	}
}

// void	test(t_command *cmds)
// {
// 	int	i;

// 	i = 0;
// 	if (!cmds)
// 		ft_printf("No commands received\n");
// 	while (cmds)
// 	{
// 		ft_printf("\n###################\n\n");
// 		ft_printf("COMMAND %d\n", ++i);
// 		ft_printf("\nArguments:\n");
// 		ft_printmtx(cmds->args);
// 		ft_printf("\n---------------\n");
// 		ft_printf("\nfiles:\n");
// 		print_filenodes(cmds->files);
// 		cmds = cmds->next;
// 	}
// 	ft_printf("\n###################\n");
// }
