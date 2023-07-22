/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/22 21:10:42 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_builtin(t_cmd *cmd)
{
	if (!cmd->args[0])
		return ;
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		cmd->builtin = 1;
}

char	**init_args(int lstsize)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (lstsize + 1));
	if (!new)
		return (NULL);
	while (i < lstsize)
	{
		new[i] = NULL;
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	clear_args(char **args)
{
	char	**temp;

	if (!args)
		return ;
	temp = args;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(args);
}

void	set_vars(int *i, int *argument)
{
	*argument = 0;
	*i = 0;
}

int	check_echo(char **args, char **word, int *argument, int *j)
{
	int	i;

	i = 1;
	if (ft_strncmp(*args, "echo", 5) || ft_strncmp(*args, "/bin/echo", 10))
	{
		while (word[0][i] == 'n')
			i++;
		if (word[0][i] != '\0')
			return (*argument = 1, args[*j] = my_strcpy(word[0]), 1);
		else
		{
			if (args[1] && !ft_strncmp(*args, "echo", 5))
				return (*j = 1, 1);
			if (args[1] && !ft_strncmp(*args, "/bin/echo", 10))
			{
				args[*j] = my_strcpy(word[0]);
				return (1);
			}
			free(word[0]);
			word[0] = my_strcpy("-n");
		}
	}
	return (0);
}
