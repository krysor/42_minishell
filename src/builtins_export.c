#include "../includes/minishell.h"

static int	var_in_envp(char *var, char **envp);
static int	ft_export_var(char *arg, char ***envp_pnt);
static int	envp_cpy(char **envp_new, char **envp_old, char *arg);

int ft_export(char **args, char ***envp)
{
	(void)args;
	(void)envp;
	return (0);
}

static int	var_in_envp(char *var, char **envp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(envp[i]);
	while (envp[i] && (ft_strncmp(envp[i], var, len)
			|| len != ft_strlen(envp[i])))
		i++;
	if (envp[i] == NULL)
		return (0);
	return (1);
}

int	ft_export_real(char **args, char ***envp)
{
	int	i;

	if (!args || !*args || !args[1] || !envp || !*envp)
		return (1);
	i = 1;
	while (args[i])
	{
		if (ft_export_var(args[i], envp))
			return (1);
		i++;
	}
	return (0);
}

/*
Add error codes
*/
static int	ft_export_var(char *arg, char ***envp_pnt)
{
	char	*sign_equal;
	char	**envp_new;
	int		envp_len;

	sign_equal = ft_memchr(arg, '=', ft_strlen(arg));
	if (!sign_equal || sign_equal - arg == 0 || var_in_envp(arg, *envp_pnt))
		return (1);
	envp_len = 0;
	while ((*envp_pnt)[envp_len])
		envp_len++;
	envp_new = malloc(sizeof(char *) * (envp_len + 2));
	if (!envp_new)
		return (1);
	if (envp_cpy(envp_new, *envp_pnt, arg))
		return (1);
	free(*envp_pnt);
	*envp_pnt = envp_new;
	return (0);
}

static int	envp_cpy(char **envp_new, char **envp_old, char *arg)
{
	int	i;

	i = -1;
	while (envp_old[++i])
		envp_new[i] = envp_old[i];
	envp_new[i] = ft_strdup(arg);
	if (!envp_new[i])
	{
		free_arr(envp_new);
		return (1);
	}
	envp_new[i + 1] = NULL;
	return (0);
}
