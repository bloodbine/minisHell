/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/27 15:40:52 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	get_outer_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && get_closing_quote(&str[i], '\''))
			return ('\'');
		if (str[i] == '\"' && get_closing_quote(&str[i], '\"'))
			return ('\"');
		i++;
	}
	return (0);
}

char	*rm_quotes(char *str, char quotes)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
	{
		write(2, "allocation failed", 17);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if (str[i] != quotes)
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

int	dollar_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (INT32_MIN);
}

int	get_seq(char *str, char **seq)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' || str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}

int	heredoc(char *delim, t_list *l_envp)
{
	char	*lptr;
	int		fd;

	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		lptr = readline("> ");
		if (!lptr)
		{
			printf("\x1b[A> ");
			break ;
		}
		if (g_signal == 1 || !ft_strncmp(lptr, delim, ft_strlen(delim) + 1))
		{
			free (lptr);
			break ;
		}
		lptr = exp_env_var(lptr, l_envp);
		write(fd, lptr, ft_strlen(lptr));
		write(fd, "\n", 1);
		free(lptr);
	}
	close(fd);
	return (0);
}
