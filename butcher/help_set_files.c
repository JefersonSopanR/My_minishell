/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_set_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-21 09:37:38 by jesopan-          #+#    #+#             */
/*   Updated: 2024-08-21 09:37:38 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_erro_pipe(void)
{
	perror("Error in pipe");
	exit(EXIT_FAILURE);
}

int	ft_check_redirections(t_redir	*redirect)
{
	int	i;

	i = 0;
	while (redirect)
	{
		if (redirect->type == T_REDIR_IN)
			i = (ft_redir_in(redirect->file));
		else if (redirect->type == T_REDIR_OUT)
			i = (ft_redir_out(redirect->file));
		else if (redirect->type == T_REDIR_APPEND)
			i = (ft_redir_append(redirect->file));
		else if (redirect->type == T_REDIR_HEREDOC)
			i = (get_here_doc(redirect->file));
		redirect = redirect->next;
	}
	return (i);
}
