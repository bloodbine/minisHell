/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:27:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 11:04:17 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		check_file(t_data *data, char *file, int check);
int		check_exist_access(char *cmd);
char	*check_paths(char *cmd, char **envp);
int		count_cmds(t_cmd *cmdlst);
void	write_output(int infd, int outfd);
void	reset_std_fds(int stdinfd, int stdoutfd);
char	**convert_env(t_list *envp);
char	*get_path_env(char **envp);
int		execute(t_data *data, t_cmd *cmd);
int		exec_command(t_data *data, t_cmd *cmd, char **envp);
int		exec_builtin(t_data *data, t_cmd *cmd);
void	child_exec(t_data *data, t_cmd *cmd, char **envp);
int		setup_fds_envlist(int *in_fd, int *out_fd, char ***elist, t_data *data);
int		handle_special(char *cmd);

#endif