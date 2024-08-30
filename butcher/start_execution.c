/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:46:21 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:46:21 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_start_execution(t_node *ast, t_global *minishell)
{
	int	exit_status;

	if (!ast)
		return (1);
	else if (ast->type == NODE_AND)
	{
		exit_status = ft_start_execution(ast->left, minishell);
		if (!exit_status)
			return (ft_start_execution(ast->right, minishell));
		return (exit_status);
	}
	else if (ast->type == NODE_OR)
	{
		exit_status = ft_start_execution(ast->left, minishell);
		if (!exit_status)
			return (exit_status);
		return (ft_start_execution(ast->right, minishell));
	}
	else
		return (ft_execute_command(ast, minishell));
	return (1);
}

void	ft_child_process(t_node *node, char **envp, t_global *minishell)
{
	if (ft_check_redirections(node->redir))
	{
		exit(EXIT_FAILURE);
	}
	execute_command(node->data, envp, minishell);
}

int	ft_execute_normal_cmd(t_node *node, t_global *minishell)
{
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Error when forking");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_child_process(node, minishell->dup_envp, minishell);
	else
	{
		waitpid(pid, &exit_status, 0);
		return (exit_status);
	}
	return (0);
}

int	ft_execute_command(t_node *node, t_global *minishell)
{
	int	exit_status;

	if (node->data[0] == '\0')
	{
		exit_status = ft_check_redirections(node->redir);
		ft_reset_fd(minishell);
		minishell->exit_status = WEXITSTATUS(exit_status);
		return (minishell->exit_status);
	}
	else if (ft_is_builtin(node->data))
	{
		exit_status = ft_execute_builtin(node, minishell);
		ft_reset_fd(minishell);
		minishell->exit_status = WEXITSTATUS(exit_status);
		return (minishell->exit_status);
	}
	else
	{
		exit_status = ft_execute_normal_cmd(node, minishell);
		minishell->exit_status = WEXITSTATUS(exit_status);
		return (minishell->exit_status);
	}
	return (0);
}

void	ft_reset_fd(t_global *minishell)
{
	int	fd_in;
	int	fd_out;

	fd_in = minishell->stdin;
	fd_out = minishell->stdout;
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
}
