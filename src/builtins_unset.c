#include "../includes/minishell.h"

static int	ft_unset_var(char *arg, char ***envp_pnt);

int	ft_unset(char **args)
{
	(void)args;
	return (0);
}

int	ft_unset_real(char **args, char ***envp)
{
	int	i;

	if (!args || !*args || !args[1] || !envp || !*envp)
		return (1);
	i = 1;
	while (args[i])
	{
		if (ft_unset_var(args[i], envp))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_unset_var(char *arg, char ***envp_pnt)
{
	int		i;
	size_t	len;
	char	**envp;

	i = 0;
	len = ft_strlen(arg);
	envp = *envp_pnt;
	while (envp[i] && (ft_strncmp(envp[i], arg, len)
			|| envp[i][len] != '='))
		i++;
	while (envp[i + 1])
	{	
		envp[i] = envp[i + 1];
		i++;
	}
	free(envp[i]);
	envp[i] = NULL;
	return (0);
}
