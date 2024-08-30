/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:44:45 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:44:45 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sort_env(t_envp **head, int swap)
{
	t_envp	*curr;
	t_envp	*next_env;
	char	*tmp_key;
	char	*tmp_value;

	while (swap)
	{
		swap = 0;
		curr = *head;
		while (curr->next != NULL)
		{
			next_env = curr->next;
			if (ft_strcmp(curr->key, next_env->key) > 0)
			{
				tmp_key = curr->key;
				tmp_value = curr->value;
				curr->key = next_env->key;
				curr->value = next_env->value;
				next_env->key = tmp_key;
				next_env->value = tmp_value;
				swap = 1;
			}
			curr = curr->next;
		}
	}
}

bool	ft_verify_key_sintax(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	ft_export_key(char *cmd, t_global *minishell)
{
	char	*key;
	char	*value;

	value = ft_get_value(cmd);
	key = ft_get_key(cmd);
	if (ft_search_key(key, value, minishell))
		return ;
	else
	{
		ft_add_back_envp(&minishell->envp, ft_new_envp(key, value));
		return ;
	}
}

t_envp	*ft_dup_envp_list(t_global *minishell)
{
	t_envp	*envp;
	t_envp	*env_list;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	envp = NULL;
	env_list = minishell->envp;
	while (env_list)
	{
		key = ft_strdup(env_list->key);
		if (env_list->value)
			value = ft_strdup(env_list->value);
		else
			value = ft_strdup("");
		ft_add_back_envp(&envp, ft_new_envp(key, value));
		env_list = env_list->next;
	}
	return (envp);
}

int	ft_export(char **cmd, t_global *minishell)
{
	t_envp	*clone_env;
	int		swap;

	swap = 1;
	clone_env = ft_dup_envp_list(minishell);
	if (!cmd[1])
	{
		ft_sort_env(&clone_env, swap);
		ft_print_export(clone_env);
	}
	else
	{
		if (!ft_verify_key_sintax(cmd[1]))
			ft_error_key(cmd[1]);
		else
			ft_export_key(cmd[1], minishell);
	}
	ft_free_envp(&clone_env);
	free_split(cmd);
	return (0);
}
