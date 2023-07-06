/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/07 00:51:00 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (str[i] == '$' || str[i] == ' ' || str[i] == '\'' || str[i] == '\"' || str[i] == '?' || str[i] == '/')
		{
			if (str[i] == '?')
				i++;
			break ;	
		}
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}

int	heredoc(char *delim, t_list *l_envp)
{
	char	*lptr;
	int		fd;
	char	quotes;
	char	*temp;
	
	quotes = get_outer_quotes(delim);
	temp = rm_quotes(my_strcpy(delim), quotes);
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
		if (g_signal == 1 || !ft_strncmp(lptr, temp, ft_strlen(temp) + 1))
		{
			free (lptr);
			break ;
		}
		if (quotes == 0)
			lptr = exp_env_var(lptr, l_envp);
		ft_fprintf(fd, "%s\n", lptr);
		free(lptr);
	}
	free(temp);
	close(fd);
	return (0);
}
