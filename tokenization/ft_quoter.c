/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 10:53:23 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 10:53:23 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_keep_in_quotes(char *line, int *i, char *quote, bool flag)
{
	if (line[*i] == *quote)
	{
		if (line[*i + 1] == '\0' || line[*i + 1] == ' ' || \
		line[*i + 1] == '\t' || line[*i + 1] == '<' || \
		line[*i + 1] == '>' || line[*i + 1] == '|' || \
		!ft_strncmp(&line[*i + 1], "&&", 2) || line[*i + 1] == ')' || \
		line[*i + 1] == '(')
		{
			(*i)++;
			return (0);
		}
		else if (line[*i + 1] != '\'' || line[*i + 1] != '"')
			return (1);
		else if (flag && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		{
			*quote = line[*i + 1];
			return (2);
		}
	}
	return (0);
}

void	ft_strcpy_data(char *data, char *data_1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] != '\'' && data[i] != '"')
			data_1[j++] = data[i++];
		else
			i++;
	}
	data_1[j] = '\0';
}

void	ft_ignore_quotes(t_token **token, char	*data, int j)
{
	char	*data_1;

	data_1 = (char *)malloc(ft_strlen(data) - j + 1);
	if (!data_1)
		return ;
	ft_strcpy_data(data, data_1);
	free(data);
	ft_add_back(token, ft_new_token(T_WORD, data_1));
}

void	ft_prep_quote_word(t_token **token, char *line, char *data, \
		t_global *minishell)
{
	char	quote;

	quote = line[minishell->i];
	(minishell->i)++;
	data = ft_append_quoted_word(line, quote, data, minishell);
	ft_add_back(token, ft_new_token(T_WORD, data));
}
