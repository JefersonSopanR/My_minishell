/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_something.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 11:10:45 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 11:10:45 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_node_data(t_global *minishell)
{
	char	*data;

	if (minishell->cur_token->type == T_WORD)
		data = ft_strdup(minishell->cur_token->data);
	else
	{
		data = ft_strdup("");
		return (data);
	}
	minishell->cur_token = minishell->cur_token->next;
	return (data);
}

t_redir	*ft_fill_redir(t_redir **redir, t_global *minishell)
{
	while (minishell->cur_token && ft_is_redir(minishell->cur_token->type) && \
		!minishell->error_type)
	{
		ft_add_redir_back(redir, ft_new_redir(minishell));
	}
	return (*redir);
}

t_node	*ft_get_cmd_node(t_global *minishell)
{
	t_node	*node;
	char	*tmp;
	char	*new_data;

	node = ft_new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->data = ft_get_node_data(minishell);
	while (minishell->cur_token && !minishell->error_type && \
	(minishell->cur_token->type == T_WORD \
	|| ft_is_redir(minishell->cur_token->type)))
	{
		if (minishell->cur_token->type == T_WORD)
		{
			tmp = ft_strjoin(node->data, " ");
			new_data = ft_strjoin(tmp, minishell->cur_token->data);
			free(tmp);
			free(node->data);
			node->data = new_data;
			minishell->cur_token = minishell->cur_token->next;
		}
		else if (ft_is_redir(minishell->cur_token->type))
			node->redir = ft_fill_redir(&node->redir, minishell);
	}
	return (node);
}
