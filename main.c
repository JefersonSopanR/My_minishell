/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:48:57 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:48:57 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_minishell(char **env, t_global *minishell)
{
	minishell->cur_token = NULL;
	minishell->error_type = E_NONE;
	minishell->token = NULL;
	minishell->ast = NULL;
	minishell->envp = NULL;
	minishell->quote = true;
	minishell->dup_envp = NULL;
	minishell->line = NULL;
	minishell->envp = ft_duplicate_envp(env, minishell);
	minishell->exit_status = 0;
	minishell->i = 0;
}

void	ft_get_minishell_ready(t_global *minishell)
{
	minishell->i = 0;
	minishell->stdin = dup(0);
	minishell->stdout = dup(STDOUT_FILENO);
}

int	ft_readline(t_global *minishell)
{
	ft_get_minishell_ready(minishell);
	minishell->line = readline("My_minishell-> ");
	if (minishell->line == NULL)
		exit(1);
	if (!minishell->line)
		return (1);
	if (!ft_strlen(minishell->line))
	{
		free(minishell->line);
		return (1);
	}
	if (minishell->line[0])
		add_history(minishell->line);
	return (0);
}

void	ft_procces_ast(t_global *minishell)
{
	ft_print_ast(minishell->ast, 0);
	minishell->exit_status = ft_start_execution(minishell->ast, minishell);
	ft_free_tokens(&minishell->token);
	ft_free_ast(minishell->ast);
}

int	main(int ac, char **av, char **env)
{
	t_global	minishell;

	((void)ac, (void)av);
	ft_init_minishell(env, &minishell);
	while (1)
	{
		if (ft_readline(&minishell))
			continue ;
		minishell.token = ft_get_tokens(minishell.line, &minishell);
		if (!minishell.token)
			continue ;
		ft_print_tokens(&minishell);
		minishell.ast = ft_create_ast(minishell.token, &minishell);
		if (minishell.ast && !minishell.error_type)
			ft_procces_ast(&minishell);
		else if (minishell.error_type)
			ft_print_error(minishell.token, &minishell);
		minishell.error_type = E_NONE;
	}
	clear_history();
	return (ft_free_envp(&minishell.envp), 0);
}
