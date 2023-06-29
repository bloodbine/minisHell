/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:27:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/29 15:29:23 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		check_file(char *file, int check);
int		check_exist_access(char *cmd);
char	*check_paths(char *cmd);
int		count_cmds(t_cmd *cmdlst);
void	write_output(int infd, int outfd);
void	reset_std_fds(int stdinfd, int stdoutfd);
char	**convert_env(t_list *envp);

#endif