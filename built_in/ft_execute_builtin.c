/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:43:47 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:43:47 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_builtin(char *command)
{
	char	**cmd;

	cmd = ft_split(command, ' ');
	if (!ft_strcmp("echo", cmd[0]) || !ft_strcmp("cd", cmd[0]) \
		|| !ft_strcmp("pwd", cmd[0]) || !ft_strcmp("export", cmd[0]) \
		|| !ft_strcmp("unset", cmd[0]) || !ft_strcmp("env", cmd[0]) \
		|| !ft_strcmp("exit", cmd[0]) || !ft_strcmp("expr", cmd[0]))
	{
		free_split(cmd);
		return (true);
	}
	free_split(cmd);
	return (false);
}

int	ft_execute_builtin(t_node *node, t_global *minishell)
{
	int		exit_status;
	char	**cmd;

	cmd = ft_split(node->data, ' ');
	exit_status = ft_check_redirections(node->redir);
	if (exit_status)
		return (ft_reset_shell(cmd, minishell), exit_status);
	if (!ft_strcmp("echo", cmd[0]))
		return (ft_echo(cmd, minishell));
	else if (!ft_strcmp("cd", cmd[0]))
		return (ft_cd(cmd, minishell));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (ft_pwd(cmd));
	else if (!ft_strcmp("export", cmd[0]))
		return (ft_export(cmd, minishell));
	else if (!ft_strcmp("unset", cmd[0]))
		return (ft_unset(cmd, minishell));
	else if (!ft_strcmp("env", cmd[0]))
		return (ft_env(cmd, minishell));
	else if (!ft_strcmp("exit", cmd[0]))
		return (ft_exit(cmd, minishell));
	else if (!ft_strcmp("expr", cmd[0]))
		return (ft_expr(cmd, minishell));
	return (1);
}

void	ft_reset_shell(char **cmd, t_global *minishell)
{
	free_split(cmd);
	ft_reset_fd(minishell);
}
