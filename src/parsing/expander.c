/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:36:25 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/24 11:53:39 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*replace_var(char *str, char *value, int var_bgn, int nvar_len)
{
	char	*new_str;
	int		val_len;

	val_len = ft_strlen(value);
	new_str = malloc(sizeof(char) * ((ft_strlen(str) - nvar_len) + val_len
				+ 1));
	if (!new_str)
	{
		display_err(NULL, NULL, "Error while allocating for expansion value",
			2);
		return (NULL);
	}
	ft_strlcpy(new_str, str, var_bgn + 1);
	ft_strlcat(new_str, value, val_len + var_bgn + 1);
	ft_strlcpy(&new_str[val_len + var_bgn], &str[var_bgn + nvar_len + 1],
		(ft_strlen(str) - var_bgn - nvar_len + 1));
	free(str);
	free(value);
	return (new_str);
}

static char	*get_var_name(char *str, int i)
{
	char	*name;
	int		bgn;
	int		len;

	bgn = i + 1;
	if (!str[bgn] || (!ft_isalnum(str[bgn]) && str[bgn] != '_'))
		return (NULL);
	len = 0;
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	name = my_malloc(sizeof(char) * len + 1);
	if (!name)
	{
		display_err(NULL, NULL, "Error while allocating expansion name", 2);
		return (NULL);
	}
	ft_strlcpy(name, &str[bgn], len + 1);
	return (name);
}

char	*expand_var(char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(str, *i);
	if (!var_name)
	{
		i++;
		return (str);
	}
	if (!get_env(var_name))
		var_value = ft_strdup("");
	else
		var_value = ft_strdup(get_env(var_name));
	str = replace_var(str, var_value, *i, ft_strlen(var_name));
	free(var_name);
	return (str);
}

char	*expand_token(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				str = replace_var(str, ft_itoa(data()->exit_code), i, 1);
			else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				str = expand_var(str, &i);
			else
				i++;
			if (!str[i])
				break ;
		}
		else
			i++;
	}
	return (str);
}
