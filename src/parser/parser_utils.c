/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/27 15:40:32 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_builtin(t_cmd *cmd)
{
	if (!cmd->args[0])
		return ;
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
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

	temp = args;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(args);
}
