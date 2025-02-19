
#include "../../inc/minishell.h"

// This is where the replacement of characters happens in the string of token
// nodes. If there is value, $<name> will be replaced by value, else if there
// is no value, $<name> will be erased

char	*replace_var(char *str, char *value, int var_bgn, int nvar_len)
{
	char	*new_str;
	int		val_len;

	val_len = ft_strlen(value);
	new_str = malloc
		(sizeof(char) * ((ft_strlen(str) - nvar_len) + val_len + 1));
	if (!new_str)
	{
		display_err(NULL, NULL,
			"Error while allocating for expansion value", 2);
		return (NULL);
	}
	ft_strlcpy(new_str, str, var_bgn + 1);
	ft_strlcat(new_str, value, val_len + var_bgn + 1);
	ft_strlcpy(&new_str[val_len + var_bgn], &str[var_bgn + nvar_len + 1], \
		(ft_strlen(str) - var_bgn - nvar_len + 1));
	free(str);
	free(value);
	return (new_str);
}

// Gets the name of the variable (what comes after a dollar sign and is
// valid character for name - export rule)

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
	name = malloc(sizeof(char) * len + 1);
	if (!name)
	{
		display_err(NULL, NULL, "Error while allocating expansion name", 2);
		return (NULL);
	}
	ft_strlcpy(name, &str[bgn], len + 1);
	return (name);
}

static char	*replace_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 17)
			str[i] = '$';
		i++;
	}
	return (str);
}

char	*expand_var(char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(str, *i);
	if (!var_name)
	{
		str[*i] = 17;
		i++;
		return (str);
	}
	if (!get_env(var_name)) // Needs to be worked on
		var_value = NULL;
	else
		var_value = ft_strdup(get_env(var_name)); // Needs to be worked on
	if (!var_value)
		var_value = ft_strdup("");
	str = replace_var(str, var_value, *i, ft_strlen(var_name));
	free(var_name);
	return (str);
}

// Main function that takes an expansion and replaces for
// its (existent or non-existent) value
// 021   17    11    DC1 (device control 1) = fk dollar flag

char	*expand_token(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				str = replace_var(str, ft_itoa(data()->exit_code), i, 1);
			else
				str = expand_var(str, &i);
			if (!str[i])
				break ;
		}
		else
			i++;
	}
	replace_dollar(str);
	return (str);
}
