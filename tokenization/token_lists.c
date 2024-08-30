/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 08:41:58 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 08:41:58 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(t_token_type type, char *data)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = data;
	token->type = type;
	return (token);
}

void	ft_add_back(t_token **token, t_token *new)
{
	t_token	*cur;

	if (!*token)
	{
		(*token) = new;
		return ;
	}
	cur = *token;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}

bool	ft_check_awk(t_token **token)
{
	t_token	*tok;

	tok = (*token);
	while (tok)
	{
		if (!ft_strcmp("awk", tok->data))
			return (true);
		tok = tok->next;
	}
	return (false);
}

void	ft_append_awk_arg(t_token **token, char *line, int *i)
{
	char	*data;
	int		start;

	start = (*i);
	if (line[*i] != '\'')
		return ;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	data = ft_substr(line, start, (*i));
	if (!data)
		return ;
	(*i)++;
	ft_add_back(token, ft_new_token(T_WORD, data));
}
