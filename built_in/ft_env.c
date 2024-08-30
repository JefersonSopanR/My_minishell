/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:43:38 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:43:38 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env, t_global *minishell)
{
	ft_print_envp(minishell->envp);
	free_split(env);
	return (0);
}
