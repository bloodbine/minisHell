/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:27:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/26 15:49:24 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

int		check_file(char *file, int check);
int		check_exist_access(char *cmd);
char	*check_paths(char *cmd);
int		exec_command(t_cmd *cmd);
int		count_cmds(t_cmd *cmdlst);
void	write_output(void);
int		execute(t_cmd *cmdlst);

#endif