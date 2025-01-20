#include "../minishell.h"

char	*get_env(char *var)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = data()->env;
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			tmp = ft_strchr(envp[i], '=');
			if (!tmp)
				break ;
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
