/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:42:17 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:42:17 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return ;
}

char	*ft_get_home_path(char *key, t_global *minishell)
{
	t_envp	*env;
	char	*home_path;

	home_path = NULL;
	env = minishell->envp;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			home_path = ft_strdup(env->value);
			return (home_path);
		}
		env = env->next;
	}
	return (home_path);
}

void	ft_cd_home(t_global *minishell)
{
	char	*path;
	char	*old_pwd;
	char	*pwd;
	char	*joiner;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	joiner = ft_strjoin("OLDPWD=", old_pwd);
	free(old_pwd);
	ft_export_key(joiner, minishell);
	free(joiner);
	path = ft_get_home_path("HOME=", minishell);
	if (path && chdir(path) == 0)
	{
		pwd = getcwd(NULL, 0);
		ft_search_key(ft_strdup("PWD="), pwd, minishell);
	}
	else
		ft_cd_error_dup(path);
	if (path)
		free(path);
}

void	ft_cd_somewhere(char *path, t_global *minishell)
{
	char	*old_pwd;
	char	*pwd;
	char	*joiner;

	joiner = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return ;
	if (chdir(path) == 0)
	{
		joiner = ft_strjoin("OLDPWD=", old_pwd);
		ft_export_key(joiner, minishell);
		pwd = getcwd(NULL, 0);
		ft_search_key(ft_strdup("PWD="), pwd, minishell);
	}
	else
		ft_cd_error(path);
	if (path)
		free(path);
	free(old_pwd);
}

int	ft_cd(char **cmd, t_global *minishell)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
	else if (i == 1)
		ft_cd_home(minishell);
	else if (i == 2)
		ft_cd_somewhere(ft_strdup(cmd[1]), minishell);
	free_split(cmd);
	return (0);
}
