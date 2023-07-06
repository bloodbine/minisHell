/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:21:34 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/06 22:41:30 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	my_env(t_list *l_envp)
{
	ft_lstiter(l_envp, print_env);
}

int	my_cd(char **path, t_data *data)
{
	char *temp;

	temp = &path[1][1];
	if (path[1] == NULL || path[1][0] == '~')
	{
		if (path[1] && path[1][1] != '\0')
		{
			path[1] = ft_strjoin("/Users/", my_getenv("USER", data->l_envp));
			path[1] = my_strjoin(path[1], temp, 1);
		}
		else
		{
			chdir(ft_strjoin("/Users/", my_getenv("USER", data->l_envp)));
			change_pwd(data->l_envp, ft_strjoin("/Users/", my_getenv("USER", data->l_envp)));
			return (0);
		}
	}
	if (path[2] != NULL)
	{
		write(2, "cd: to many arguments\n", 22);
		return(1);
	}
	if (path[1][0] != '/')
	{
		path[1] = my_strjoin("/", path[1], 2);
		path[1] = my_strjoin(my_pwd(data, 1), path[1], 2);
	}
	if (chdir(path[1]))
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, path[1], ft_strlen(path[1]));
		write(2, "\n", 1);
		return(1);
	}
	change_pwd(data->l_envp, path[1]);
	return (0);
}

char	*my_pwd(t_data *data, int id)
{
	t_list	*env;
	t_envp	*cont;

	env = data->l_envp;
	while (1)
	{
		cont = ((t_envp *)(env->content));
		if (cont->status && ft_strncmp(cont->word, "PWD=", 4) == 0)
			break ;
		env = env->next;
		if (env == NULL)
			exit(1);
	}
	if (!id)
	{
		write(STDOUT_FILENO, (cont->word + 4), ft_strlen(cont->word + 4));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (&cont->word[4]);
}

void	my_echo(char **argv)
{
	int	i;

	i = 1;
	if (argv[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (!ft_strncmp(argv[1], "-n", 3))
		i = 2;
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (ft_strncmp(argv[1], "-n", 3))
		write(STDOUT_FILENO, "\n", 1);
}

int	my_exit(char **args)
{
	if (!args[1])
		exit(0);
	if (args[2] && ft_atoi(args[1]) != 0)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (ft_atoi(args[1]) == 0 && ft_isdigit(args[1][0]))
		exit (0);
	if (ft_atoi(args[1]) && args[2] == NULL)
		exit((256 + ft_atoi(args[1])) % 256);
	else
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		exit (255);
	}
		
}