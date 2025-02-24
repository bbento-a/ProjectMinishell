#include "../../inc/minishell.h"

char	*get_env(char *var)
{
	t_env	*envp;
	char	*tmp;

	envp = data()->env;
	while(envp)
	{
		// printf("envp[i]: %s\n", envp[i]);
		if (ft_strncmp(envp->value, var, ft_strlen(var)) == 0) // envp var name needs a size cmp before this condition
		{
			tmp = ft_strchr(envp->value, '=');
			// printf("tmp: %s\n", tmp);
			// printf("tmp: %ld; size of tmp: %ld\n", ft_strlen(envp[i]), ft_strlen(tmp));
			// printf("tmp - size of tmp: %ld\n", ft_strlen(envp[i]) - ft_strlen(tmp));
			if (!tmp || ft_strlen(envp->value) - ft_strlen(tmp) != ft_strlen(var))
				break ;
			tmp++;
			return (tmp);
		}
		envp = envp->next;
	}
	return (NULL);
}
