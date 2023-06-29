/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:27:08 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/29 15:33:10 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_echo(char **argv)
{
	int		i;

	i = 0;
	if (ft_strncmp(argv[1], "-n", 3) == 0)
		i = 1;
	while (argv[++i] != NULL)
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
	if (ft_strncmp(argv[1], "-n", 3) != 0)
		write(STDOUT_FILENO, "\n", 2);
}

void	my_pwd(t_data *data)
{
	t_list	*env;
	char	*cont;

	env = data->l_envp;
	while (1)
	{
		cont = ((char *)(env->content));
		if (ft_strncmp(cont, "PWD", 3) == 0)
			break ;
		env = env->next;
		if (env == NULL)
			exit(1);
	}
	write(STDOUT_FILENO, (cont + 4), ft_strlen(cont + 4));
	write(STDOUT_FILENO, "\n", 2);
}

void	exec_builtin(t_data *data, char *cmd, char **argv)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		my_echo(argv);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		my_pwd(data);
	exit(0);
}
