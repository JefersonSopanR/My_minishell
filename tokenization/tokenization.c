/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:13:04 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:13:04 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_dollar(char *line, int *i)
{
	char	quote;
	int		start;
	char	*data;

	quote = line[*i];
	start = *i;
	data = NULL;
	(*i)++;
	while (line[*i] != quote)
		(*i)++;
	data = ft_substr(line, start, (*i));
	if (!data)
		return (NULL);
	(*i)++;
	return (data);
}

void	ft_inside_quote(t_token **token, char *line, t_global *minishell)
{
	char	*data;

	if (line[minishell->i + 1] == '$')
	{
		data = ft_handle_dollar(line, &minishell->i);
		ft_add_back(token, ft_new_token(T_WORD, data));
		return ;
	}
	data = ft_strdup("");
	ft_prep_quote_word(token, line, data, minishell);
	return ;
}

void	ft_append_word(t_token **token, char *line, t_global *minishell)
{
	int		start;
	char	*data;

	if (line[minishell->i] == '\'' || line[minishell->i] == '"')
	{
		ft_inside_quote(token, line, minishell);
		return ;
	}
	start = (minishell->i);
	while (line[minishell->i] && !ft_is_not_op(line, &minishell->i))
	{
		(minishell->i)++;
		if (line[minishell->i] == '\'' || line[minishell->i] == '"')
		{
			data = ft_substr(line, start, (minishell->i) - start);
			ft_prep_quote_word(token, line, data, minishell);
			return ;
		}
	}
	data = ft_substr(line, start, (minishell->i) - start);
	ft_add_back(token, ft_new_token(T_WORD, data));
}

t_token	*ft_procces_line(char *line, t_global *minishell)
{
	t_token	*token;

	token = NULL;
	while (line[minishell->i])
	{
		if (line[minishell->i] == ' ')
			minishell->i++;
		else if (line[minishell->i] == '>' || line[minishell->i] == '<' \
		|| line[minishell->i] == '(' || line[minishell->i] == ')' \
		|| line[minishell->i] == '|' \
		|| !ft_strncmp(&line[minishell->i], "&&", 2))
			ft_identify_operators(&token, line, &minishell->i);
		else if (ft_check_awk(&token))
			ft_append_awk_arg(&token, line, &minishell->i);
		else
			ft_append_word(&token, line, minishell);
	}
	return (token);
}

t_token	*ft_get_tokens(char *line, t_global *minishell)
{
	t_token	*token;

	if (ft_check_quotes(line))
	{
		free(line);
		return (NULL);
	}
	token = ft_procces_line(line, minishell);
	free(line);
	return (token);
}
