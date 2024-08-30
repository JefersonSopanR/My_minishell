/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:45:19 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:45:19 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_env(char *key, t_global *minishell)
{
	t_envp	*env;
	t_envp	*previous;
	char	*id_key;

	previous = NULL;
	env = minishell->envp;
	while (env)
	{
		id_key = ft_substr(env->key, 0, ft_strlen(env->key) - 1);
		if (!ft_strcmp(id_key, key))
		{
			free(id_key);
			if (previous)
				previous->next = env->next;
			else
				minishell->envp = env->next;
			free(env);
			return ;
		}
		free(id_key);
		previous = env;
		env = env->next;
	}
}

int	ft_unset(char **cmd, t_global *minishell)
{
	int	i;

	i = 1;
	if (!cmd[i])
	{
		free_split(cmd);
		return (0);
	}
	while (cmd[i])
	{
		ft_delete_env(cmd[i], minishell);
		i++;
	}
	free_split(cmd);
	return (0);
}
