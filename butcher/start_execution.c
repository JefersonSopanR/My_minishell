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

int	ft_get_exit_status(int status)
{
	if (status == 512)
		return (127);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	ft_child_pipe(t_node *ast, int pfd[], bool is_left, t_global *minishell)
{
	int	exit_status;

	if (is_left)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
	}
	else if (!is_left)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
	}
	exit_status = ft_start_execution(ast, minishell, true);
	ft_free_tokens(&minishell->token);
	ft_free_ast(minishell->ast);
	clear_history();
	ft_free_envp(&minishell->envp);
	exit(exit_status);
}

int	ft_execute_pipe(t_node *ast, t_global *minishell)
{
	int	exit_status;
	int	pfd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	pipe(pfd);
	left_pid = fork();
	if (!left_pid)
		ft_child_pipe(ast->left, pfd, true, minishell);
	else
	{
		right_pid = fork();
		if (!right_pid)
			ft_child_pipe(ast->right, pfd, false, minishell);
		else
		{
			close(pfd[0]);
			close(pfd[1]);
			waitpid(left_pid, &exit_status, 0);
			waitpid(right_pid, &exit_status, 0);
			return (ft_get_exit_status(exit_status));
		}
	}
	return (0);
}

int	ft_start_execution(t_node *ast, t_global *minishell, bool in_pipe)
{
	int	exit_status;

	if (!ast)
		return (1);
	else if (ast->type == NODE_AND)
	{
		exit_status = ft_start_execution(ast->left, minishell, false);
		if (!exit_status)
			return (ft_start_execution(ast->right, minishell, false));
		return (exit_status);
	}
	else if (ast->type == NODE_OR)
	{
		exit_status = ft_start_execution(ast->left, minishell, false);
		if (!exit_status)
			return (exit_status);
		return (ft_start_execution(ast->right, minishell, false));
	}
	else if (ast->type == NODE_PIPE)
		return (ft_execute_pipe(ast, minishell));
	else
		return (ft_execute_command(ast, minishell, in_pipe));
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

int	ft_execute_command(t_node *node, t_global *minishell, bool in_pipe)
{
	int	exit_status;

	if (node->data[0] == '\0')
	{
		exit_status = ft_check_redirections(node->redir);
		ft_reset_fd(minishell, in_pipe);
		return (exit_status);
	}
	else if (ft_is_builtin(node->data))
	{
		exit_status = ft_execute_builtin(node, minishell, in_pipe);
		ft_reset_fd(minishell, in_pipe);
		return (exit_status);
	}
	else
	{
		exit_status = ft_execute_normal_cmd(node, minishell);
		return (ft_get_exit_status(exit_status));
	}
	return (0);
}

void	ft_reset_fd(t_global *minishell, bool in_pipe)
{
	int	fd_in;
	int	fd_out;

	if (in_pipe)
		return ;
	fd_in = minishell->stdin;
	fd_out = minishell->stdout;
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
}
