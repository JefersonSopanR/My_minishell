/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-30 13:38:23 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-30 13:38:23 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg_err_expr(char *msg)
{
	ft_putstr_fd("expr: syntax error: unexpected argument ‘", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
}

bool	ft_verify_arg(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (i % 2 == 0)
		{
			if (!ft_strchr("+-=", arg[i][0]) || ft_strlen(arg[i]) != 1)
				return (false);
		}
		else
		{
			if (ft_strcmp(arg[i], "$?"))
				return (false);
		}
		i++;
	}
	if (i % 2 != 0)
		return (false);
	return (true);
}

int	ft_get_result(char **arg, t_global *minishell)
{
	int		i;
	int		result;
	char	sign;

	sign = arg[2][0];
	result = minishell->exit_status;
	i = 1;
	if (!ft_strcmp(arg[2], "="))
		return (1);
	while (arg[i])
	{
		if (i % 2 == 0)
		{
			sign = arg[i][0];
			if (sign == '+')
				result += minishell->exit_status;
			else if (sign == '-')
				result -= minishell->exit_status;
			else if (sign == '=')
				return (0);
		}
		i++;
	}
	return (result);
}

int	ft_expr(char **cmd, t_global *minishell)
{
	int	result;

	result = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("expr: missing operand\n", 2);
		free_split(cmd);
		return (2);
	}
	if (cmd[2])
	{
		if (!ft_verify_arg(cmd))
		{
			ft_msg_err_expr(cmd[2]);
			return (free_split(cmd), 2);
		}
		result = ft_get_result(cmd, minishell);
	}
	else if (!ft_strcmp(cmd[1], "$?"))
		result = minishell->exit_status;
	ft_printf("%d\n", result);
	free_split(cmd);
	return (0);
}
