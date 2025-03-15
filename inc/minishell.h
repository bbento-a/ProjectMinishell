/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:12:37 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 08:25:57 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//
//  LIBRARIES, HEADERS AND MACROS
//

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"

# include <readline/readline.h>
# include <readline/history.h>

//
//  STRUCTS
//

typedef struct s_minishell
{
	char		hld_flag; // hold flag for quotes
	char		*shlvl;
	int			exit_code;
	int			last_exit_status;
	bool		prompt_flag; // signals flag
	bool		error_parse;

	t_line		*prompt;
	t_command	*cmds;
	t_env		*env;

}	t_minishell;

//
//	FUNCTIONS
//

//
//	MISCELLANEOUS
//

// data.c

t_minishell	*data(void);
void		init_data(char **envp);
t_env		*parse_envp(char **envp);

// exit_functions.c
int			display_err(char *local, char *arg, char *error_msg, int err_code);

// free_functions.c
void		free_files(t_files	*files);
void		free_cmds(t_command **cmds);
void		free_array(char **mtx);
void		clear_linelst(t_line **lst);
void		clear_fork(char *path, char **env_array);
void		clear_env(t_env *env);
void		clear_memory(t_command *commands);

// ft_functions.c
bool		symbol_cmp(char *sign, char c);
void		define_flg(char c);
int			ft_mtxlen(char **mtx);
void		ft_freemtx(char **mtx);
void		define_white_space(t_line *node, char *line, int bgn);
t_type		define_type(t_line *node);
int			is_builtin(char *command_name);
void		*my_malloc(size_t size);

// lst_functions.c
t_line		*find_lastnode(t_line *lst);

// ft_debug.c
void		ft_printmtx(char **mtx);
void		ft_printlist(t_line *lst);
void		test(t_command *cmds);
void		print_filenodes(t_files *files);
void		ft_printfiles(t_files *files);
void		ft_print_env(t_env *env);

#endif