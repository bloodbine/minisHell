/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:48:42 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/22 21:18:50 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_heredoc(int *fd, char **filename)
{
	static int	heredoc;
	char		*temp;

	temp = ft_itoa(heredoc);
	*fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(*filename);
	*filename = my_strcpy(temp);
	free(temp);
	heredoc++;
	if (*fd == -1)
		return (-1);
	return (0);
}

int	heredoc(char **delim, t_data *data, int fd)
{
	char	*lptr;
	char	quotes;
	char	*temp;

	quotes = get_outer_quotes(*delim);
	temp = rm_quotes(my_strcpy(*delim), quotes);
	if (open_heredoc(&fd, delim) == -1)
		return (free(temp), -1);
	while (1)
	{
		lptr = readline("> ");
		if (!lptr)
			return (printf("\x1b[A> "), free(temp), close(fd), 0);
		if (g_signal == 1 || !ft_strncmp(lptr, temp, ft_strlen(temp) + 1))
			return (free(lptr), free(temp), close(fd), 0);
		if (quotes == 0)
			lptr = exp_env_var(lptr, data);
		ft_fprintf(fd, "%s\n", lptr);
		free(lptr);
	}
}
