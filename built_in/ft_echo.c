/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:43:24 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:43:24 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_get_env_var(char *env_word, t_global *minishell)
{
	t_envp	*envp;

	envp = minishell->envp;
	while (envp)
	{
		if (!ft_strncmp(env_word, envp->key, ft_strlen(envp->key) - 1))
		{
			if (!env_word[ft_strlen(envp->key) - 1])
				ft_putstr_fd(envp->value, 1);
		}
		envp = envp->next;
	}
	return ;
}

void	ft_print_exit_status(int *i, t_global *minishell)
{
	ft_printf("%d", minishell->exit_status);
	(*i)++;
	return ;
}

void	ft_print_echo(char *word, t_global *minishell)
{
	int		i;
	char	*quote;

	quote = NULL;
	quote = ft_get_echo_quote(word);
	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && quote == NULL && word[i + 1] != '?')
		{
			i++;
			if (!word[i])
				ft_putchar_fd('$', 1);
			else
				ft_get_env_var(&word[i], minishell);
			break ;
		}
		else if (word[i] == '$' && word[i + 1] == '?')
			ft_print_exit_status(&i, minishell);
		else
			ft_putchar_fd(word[i], 1);
		i++;
	}
	ft_putchar_fd(' ', 1);
}

int	ft_echo(char **cmd, t_global *minishell)
{
	int		i;
	bool	new_line;

	new_line = true;
	i = 1;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (free_split(cmd), 0);
	}
	if (ft_check_new_line(cmd[1]))
	{
		i++;
		new_line = false;
	}
	while (cmd[i])
	{
		ft_print_echo(cmd[i++], minishell);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	free_split(cmd);
	return (0);
}
