/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:45:30 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:45:30 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_path(char *path, char *cmd)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

void	ft_free_get_path(char **split_path, t_global *minishell)
{
	free_split(split_path);
	ft_free_ast(minishell->ast);
	ft_free_tokens(&minishell->token);
	return ;
}

char	*get_path(char *cmd, char **envp, t_global *minishell)
{
	char	**split_path;
	char	*cmd_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i] != NULL)
	{
		cmd_path = create_path(split_path[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_split(split_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free_get_path(split_path, minishell);
	return (NULL);
}

void	execute_command(char *command, char **envp, t_global *minishell)
{
	char	**split_command;
	char	*path;

	path = NULL;
	if (command == NULL || command[0] == '\0')
		return ;
	if (ft_strchr(command, '\''))
		split_command = ft_handle_cmd_quotes(command);
	else
		split_command = ft_split(command, ' ');
	if (ft_strnstr(split_command[0], "/", ft_strlen(split_command[0])))
	{
		if (access(split_command[0], F_OK | X_OK) == 0)
			path = split_command[0];
	}
	else
		path = get_path(split_command[0], envp, minishell);
	if (path == NULL)
		ft_command_not_found(split_command);
	if (execve(path, split_command, envp) == -1)
	{
		free(path);
		ft_command_not_found(split_command);
	}
}

void	ft_command_not_found(char **split_command)
{
	write(2, "command not found: ", 19);
	write(2, split_command[0], ft_strlen(split_command[0]));
	write(2, "\n", 1);
	free_split(split_command);
	exit(EXIT_FAILURE);
}
