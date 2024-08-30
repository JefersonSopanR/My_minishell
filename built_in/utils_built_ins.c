/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_ins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 09:05:31 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 09:05:31 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_error_dup(char *path)
{
	if (path)
		ft_cd_error(path);
	else
		ft_cd_error("HOME");
	return ;
}

bool	ft_check_equal(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	if (key[i] == '=')
		return (true);
	return (false);
}

bool	ft_search_key(char *key, char *value, t_global *minishell)
{
	t_envp	*env;

	env = minishell->envp;
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
		{
			free(env->key);
			free(env->value);
			env->key = key;
			env->value = value;
			return (true);
		}
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (true);
		env = env->next;
	}
	return (false);
}

void	ft_error_key(char *key)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	ft_print_export(t_envp *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		if (envp->value[0] == '\0')
		{
			printf("declare -x %s", envp->key);
			if (ft_check_equal(envp->key))
				printf("\"\"");
			printf("\n");
		}
		else
			printf("declare -x %s\"%s\"\n", envp->key, envp->value);
		envp = envp->next;
	}
}
