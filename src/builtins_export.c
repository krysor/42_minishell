#include "../includes/minishell.h"

static int	envp_cpy(char **envp_new, char **envp_old, char *arg);
static int	delete_existing_arg(char *arg, char ***envp_pnt);

int	get_i_var(char *var, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i] && (ft_strncmp(envp[i], var, len) || envp[i][len] != '='))
		i++;
	if (envp[i])
		return (i);
	return (-1);
}

int	ft_export(char **args, char ***envp)
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
int	ft_export_var(char *arg, char ***envp_pnt)//if already exists, delete old one and add new oen
{
	int		len_envp_old;
	char	**envp_new;

	if (!ft_memchr(arg, '=', ft_strlen(arg)))
		return (0);
	if (arg[0] == '=')
		return (1);
	if (delete_existing_arg(arg, envp_pnt))
		return (1);
	len_envp_old = 0;
	while ((*envp_pnt)[len_envp_old])
		len_envp_old++;
	envp_new = malloc(sizeof(char *) * (len_envp_old + 2));
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

static int	delete_existing_arg(char *arg, char ***envp_pnt)
{
	char	*temp_arg;
	int		i = 0;
	
	temp_arg = ft_strdup(arg);
	if (!temp_arg)
		return (1);
	while (temp_arg[i] != '=')
		i++;
	temp_arg[i] = '\0';	
	if (get_i_var(temp_arg, *envp_pnt) != -1)
	 	ft_unset_var(temp_arg, envp_pnt);
	free(temp_arg);
	return (0);
}

/*
int	ft_export_var(char *arg, char ***envp_pnt)//if already exists, delete old one and add new oen
{
	char	*sign_equal;
	char	**envp_new;
	int		envp_len;

	sign_equal = ft_memchr(arg, '=', ft_strlen(arg));
	if (!sign_equal || sign_equal - arg == 0)
		return (1);

	// if (get_i_var(arg, *envp_pnt) != -1)//deze moet aangepast worden want arg is niet gelijk aan arg bij unset
	// 	ft_unset_var(arg, envp_pnt);
		
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
}*/

