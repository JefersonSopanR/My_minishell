/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:25:19 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:25:19 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_primary(t_global *shell)
{
	t_node	*node;

	node = NULL;
	if (!shell->cur_token || !ft_is_cmd(shell->cur_token))
	{
		shell->error_type = E_SYNTAX;
		return (NULL);
	}
	else if (shell->cur_token && shell->cur_token->type == T_O_PARENTHESIS)
	{
		shell->cur_token = shell->cur_token->next;
		if (!shell->cur_token)
			return (shell->error_type = E_SYNTAX, node);
		node = ft_expression(0, shell);
		if (!shell->cur_token || shell->cur_token->type != T_C_PARENTHESIS)
			shell->error_type = E_SYNTAX;
		else
			shell->cur_token = shell->cur_token->next;
		return (node);
	}
	else if (shell->cur_token && (shell->cur_token->type == T_WORD \
		|| ft_is_redir(shell->cur_token->type)))
		return (ft_get_cmd_node(shell));
	return (node);
}

t_node	*ft_expression(int min_prec, t_global *minishell)
{
	t_node			*left;
	t_node			*right;
	int				next_prec;
	t_token_type	op;

	left = ft_primary(minishell);
	if (!left)
		return (NULL);
	while (minishell->cur_token && !ft_is_cmd(minishell->cur_token) && \
		ft_prec(minishell->cur_token->type) >= min_prec \
		&& !minishell->error_type)
	{
		op = minishell->cur_token->type;
		minishell->cur_token = minishell->cur_token->next;
		if (!minishell->cur_token || !ft_is_cmd(minishell->cur_token))
			return (minishell->error_type = E_SYNTAX, left);
		next_prec = ft_prec(minishell->cur_token->type) + 1;
		right = ft_expression(next_prec, minishell);
		if (!right)
			return (left);
		left = ft_connect_nodes(op, left, right);
	}
	return (left);
}

t_node	*ft_create_ast(t_token *token, t_global *minishell)
{
	t_node	*ast;

	minishell->cur_token = token;
	ast = ft_expression(0, minishell);
	if (minishell->cur_token)
	{
		minishell->error_type = E_SYNTAX;
		return (ast);
	}
	return (ast);
}
