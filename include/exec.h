/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:27:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 17:39:48 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	init_signals_child(struct termios *termios_mirror);
void	signal_error(t_data *data);
void	signals_parent(void);
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
int		handle_special(t_data *data, char *cmd);

#endif