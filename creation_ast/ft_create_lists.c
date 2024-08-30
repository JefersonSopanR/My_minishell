/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:23:54 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:23:54 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_new_node(t_node_type type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

t_redir	*ft_new_redir(t_global *minishell)
{
	t_redir			*redir;
	t_token_type	type;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	type = minishell->cur_token->type;
	redir->type = type;
	minishell->cur_token = minishell->cur_token->next;
	if (minishell->cur_token && minishell->cur_token->type == T_WORD)
	{
		redir->file = ft_strdup(minishell->cur_token->data);
		minishell->cur_token = minishell->cur_token->next;
	}
	else
		minishell->error_type = E_SYNTAX;
	return (redir);
}

void	ft_add_redir_back(t_redir **redir, t_redir *new)
{
	t_redir	*cur;

	if (!*redir)
	{
		*redir = new;
		return ;
	}
	cur = *redir;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}
