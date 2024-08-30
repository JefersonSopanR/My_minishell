/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-30 13:31:49 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-30 13:31:49 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_quoted_word(char *line, char q, char *data, t_global *shell)
{
	char	*join;
	char	*tmp;
	int		j;

	j = (shell->i);
	while (line[shell->i] && shell->quote)
	{
		if (line[shell->i] == q)
		{
			tmp = ft_substr(line, j, (shell->i) - j);
			join = ft_strjoin(data, tmp);
			free(tmp);
			free(data);
			data = join;
			if (!ft_keep_in_quotes(line, &shell->i, &q, false))
				return (data);
			if (ft_keep_in_quotes(line, &shell->i, &q, false) == 1)
				data = ft_join_normal_data(line, data, &q, shell);
			(shell->i) += ft_keep_in_quotes(line, &shell->i, &q, true);
			j = (shell->i);
		}
		else
			(shell->i)++;
	}
	return (shell->quote = true, data);
}

char	*ft_join_normal_data(char *line, char *data, char *q, t_global *shell)
{
	char	*tmp;
	char	*join;
	int		start;

	(shell->i)++;
	start = (shell->i);
	while (line[shell->i] && !ft_is_not_op(line, &shell->i) && \
	line[shell->i] != '\'' && line[shell->i] != '"')
		(shell->i)++;
	if (ft_is_not_op(line, &shell->i))
		shell->quote = false;
	else if (line[shell->i] == '\'' || line[shell->i] == '"')
		*q = line[shell->i];
	tmp = ft_substr(line, start, (shell->i) - start);
	join = ft_strjoin(data, tmp);
	free(tmp);
	free(data);
	data = join;
	return (data);
}
