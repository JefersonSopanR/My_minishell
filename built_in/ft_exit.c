/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:44:26 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:44:26 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(char **cmd, int j, bool sign, t_global *minishell)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		while (cmd[1][j])
		{
			if ((cmd[1][0] == '-' || cmd[1][0] == '+') &&
				(ft_isdigit(cmd[1][1])) && !sign)
			{
				sign = true;
				j++;
			}
			else if (!ft_isdigit(cmd[1][j++]))
				ft_numeric_argument_required(cmd[1], cmd, minishell);
		}
		if (i > 2)
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			ft_free_everything(cmd, 1, minishell);
		}
		i++;
	}
	return (i);
}

void	ft_numeric_argument_required(const char *s, char **cmd, \
		t_global *minishell)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd((char *)s, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_everything(cmd, 2, minishell);
}

long	ft_exit_atoi(const char *s, char **cmd, t_global *minishell)
{
	long long	result;
	int			sign;
	int			checker;

	checker = 0;
	result = 0;
	sign = 1;
	while (*s == ' ' || *s == '\t' || *s == '\n' || \
			*s == '\r' || *s == '\f' || *s == '\v')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (sign == -1)
		checker = 1;
	while (ft_isdigit(*s))
	{
		if ((result > (((LONG_MAX - (*s - '0')) / 10) + checker)))
			ft_numeric_argument_required(cmd[1], cmd, minishell);
		result = result * 10 + (*s++ - '0');
	}
	return ((result * sign) % 256);
}

int	ft_exit(char **cmd, t_global *minishell)
{
	long	num;
	bool	sign;
	int		j;

	sign = false;
	j = 0;
	num = 0;
	if (!cmd[1])
		ft_free_everything(cmd, num, minishell);
	if (ft_count_args(cmd, j, sign, minishell) == 2)
		num = ft_exit_atoi(cmd[1], cmd, minishell);
	ft_free_everything(cmd, num, minishell);
	exit(0);
}

void	ft_free_everything(char **cmd, int num, t_global *minishell)
{
	free_split(cmd);
	ft_free_tokens(&minishell->token);
	ft_free_ast(minishell->ast);
	clear_history();
	ft_free_envp(&minishell->envp);
	exit(num);
}
