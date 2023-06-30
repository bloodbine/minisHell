/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:27:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/30 22:27:18 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	print_env(void *data);
void	my_env(t_list *l_envp);
int		my_cd(char** path, t_data *data);
char	*my_pwd(t_data *data, int id);
void	my_echo(char **argv);
void 	change_PWD(t_list *l_envp, char *path);
void	my_exit(char **args);
void	my_export_unset(char **args, t_data *data);
void	toggle_env_var(char *arg, t_list *l_envp);

#endif
