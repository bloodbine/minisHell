/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:03:39 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/08 14:12:38 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_output(int infd, int outfd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(infd);
		if (line == NULL)
			break ;
		write(outfd, line, ft_strlen(line));
		free(line);
	}
}

void	reset_std_fds(int stdinfd, int stdoutfd)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdinfd, STDIN_FILENO);
	dup2(stdoutfd, STDOUT_FILENO);
	close(stdinfd);
	close(stdoutfd);
}

char	**convert_env(t_list *envp)
{
	char	**list;
	t_list	*temp;
	int		i;

	temp = envp;
	i = 0;
	while (temp != NULL)
	{
		i += 1;
		temp = temp->next;
	}
	list = malloc((i + 1) * sizeof(char *));
	if (list == NULL)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp != NULL)
	{
		list[i] = ((((t_content *)(temp->content))->word));
		i += 1;
		temp = temp->next;
	}
	list[i] = NULL;
	return (list);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = -1;
	while (1)
	{
		if (envp[++i] == NULL)
			return (NULL);
		else if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (envp[i]);
	}
}
