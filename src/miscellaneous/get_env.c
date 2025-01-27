#include "../inc/minishell.h"

char	*get_env(char *var)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = data()->env;
	i = 0;
	while(envp[i])
	{
		// printf("envp[i]: %s\n", envp[i]);
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0) // envp var name needs a size cmp before this condition
		{
			tmp = ft_strchr(envp[i], '=');
			// printf("tmp: %s\n", tmp);
			// printf("tmp: %ld; size of tmp: %ld\n", ft_strlen(envp[i]), ft_strlen(tmp));
			// printf("tmp - size of tmp: %ld\n", ft_strlen(envp[i]) - ft_strlen(tmp));
			if (!tmp || ft_strlen(envp[i]) - ft_strlen(tmp) != ft_strlen(var))
				break ;
			return (tmp++);
		}
		i++;
	}
	return (NULL);
}
