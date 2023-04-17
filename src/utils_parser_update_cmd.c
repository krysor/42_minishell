#include "../includes/minishell.h"

int	set_cmd_builtin(t_cmd *cmd)
{
	char	*function;
	size_t	len;

	if (!cmd->args || !cmd->args[0])
		return (0);
	function = cmd->args[0];
	len = ft_strlen(function);
	if (!ft_strncmp(function, "echo", len) && len == ft_strlen("echo"))
		cmd->builtin = &ft_echo;
	else if (!ft_strncmp(function, CD, len) && len == ft_strlen(CD))
		cmd->builtin = &ft_cd;
	else if (!ft_strncmp(function, PWD, len) && len == ft_strlen(PWD))
		cmd->builtin = &ft_pwd;
	else if (!ft_strncmp(function, EXPORT, len) && len == ft_strlen(EXPORT))
		cmd->builtin = &ft_export;
	else if (!ft_strncmp(function, UNSET, len) && len == ft_strlen(UNSET))
		cmd->builtin = &ft_unset;
	else if (!ft_strncmp(function, ENV, len) && len == ft_strlen(ENV))
		cmd->builtin = &ft_env;
	else if (!ft_strncmp(function, EXIT, len) && len == ft_strlen(EXIT))
		cmd->builtin = &ft_exit;
	else
		return (1);
	return (0);
}
