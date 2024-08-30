/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:18:25 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:18:25 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_global *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token)
	{
		printf("TYPE-> %d  DATA-> %s\n", token->type, token->data);
		token = token->next;
	}
}

void	ft_print_ast(t_node *ast, int depth)
{
	int	i;

	i = depth;
	if (!ast)
		return ;
	while (i > 0)
	{
		printf(" ");
		i--;
	}
	printf("NODE_TYPE-> %d  ", ast->type);
	if (ast->redir && (ast->redir->type == T_REDIR_IN \
	|| ast->redir->type == T_REDIR_HEREDOC))
		printf("NODE_REDIR-> %s ", ast->redir->file);
	if (ast->data)
		printf("NODE_DATA-> %s ", ast->data);
	if (ast->redir && (ast->redir->type == T_REDIR_OUT \
	|| ast->redir->type == T_REDIR_APPEND))
		printf("NODE_REDIR-> %s ", ast->redir->file);
	printf("\n");
	ft_print_ast(ast->left, depth + 1);
	ft_print_ast(ast->right, depth + 1);
}

void	ft_print_error(t_token *token, t_global *minishell)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	if (!minishell->cur_token)
	{
		while (token && token->next != minishell->cur_token)
			token = token->next;
		if (ft_is_redir(token->type))
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(token->data, 2);
	}
	else if (minishell->cur_token->type == T_O_PARENTHESIS \
		&& minishell->cur_token->next)
	{
		minishell->cur_token = minishell->cur_token->next;
		ft_putstr_fd(minishell->cur_token->data, 2);
	}
	else if (minishell->cur_token->data)
		ft_putstr_fd(minishell->cur_token->data, 2);
	ft_putstr_fd("'\n", 2);
	ft_free_tokens(&minishell->token);
	ft_free_ast(minishell->ast);
}

void	ft_print_envp(t_envp *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		if (ft_check_equal(envp->key))
		{
			printf("%s", envp->key);
			if (envp->value)
				printf("%s", envp->value);
			printf("\n");
		}
		envp = envp->next;
	}
}
