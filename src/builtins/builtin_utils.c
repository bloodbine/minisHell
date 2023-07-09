/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:21:58 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/09 11:31:24 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_pwd(t_list *l_envp, char *path)
{
	t_envp	*content;

	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	while (l_envp)
	{
		content = (t_envp *)(l_envp->content);
		if (!ft_strncmp(content->word, "PWD=", 4))
		{
			free (content->word);
			content->word = my_strjoin("PWD=", path, 0);
		}
		l_envp = l_envp->next;
	}
	//need to change oldpwd
}

void	print_env(void *data)
{
	t_envp	*content;

	content = (t_envp *)data;
	if (content->status == 1)
		printf("%s\n", content->word);
}

t_list	*check_exist_env(t_data *data, char *envname)
{
	t_list	*envp;
	int		checklen;

	envp = data->l_envp;
	if (ft_strchr(envname, '=') != NULL)
		checklen = ft_strlen(envname) - ft_strlen((ft_strchr(envname, '=')));
	else
		checklen = ft_strlen(envname);
	while (envp != NULL)
	{
		if (!ft_strncmp((((t_envp *)(envp->content))->word), envname, checklen))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

int	exec_builtin(t_data *data, t_cmd *cmd)
{
	int	cmdlen;

	cmdlen = ft_strlen(cmd->args[0]) + 1;
	if (ft_strncmp(cmd->args[0], "exit", cmdlen) == 0)
		data->my_errno = my_exit(cmd->args);
	if (ft_strncmp(cmd->args[0], "echo", cmdlen) == 0)
		my_echo(cmd->args);
	if (ft_strncmp(cmd->args[0], "env", cmdlen) == 0)
		my_env(data->l_envp);
	if (ft_strncmp(cmd->args[0], "pwd", cmdlen) == 0)
		my_pwd(data, 0);
	if (ft_strncmp(cmd->args[0], "cd", cmdlen) == 0)
		data->my_errno = my_cd(cmd->args, data);
	if (ft_strncmp(cmd->args[0], "export", cmdlen) == 0)
		data->my_errno = my_export(cmd->args, data);
	if (ft_strncmp(cmd->args[0], "unset", cmdlen) == 0)
		data->my_errno = my_unset(cmd->args, data);
	return (data->my_errno);
}
