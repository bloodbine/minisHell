/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:27:55 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 16:16:28 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	print_env(void *data);
void	change_pwd(t_list *l_envp);
void	toggle_env_var(char *arg, t_list *l_envp);
t_list	*check_exist_env(t_data *data, char *envname);
t_envp	*init_content_envp(char *str);
int		my_env(t_list *l_envp);
int		my_cd(char **path, t_data *data);
int		my_exit(char **args);
char	*my_pwd(t_data *data, int id);
int		my_echo(char **argv);
int		my_unset(char **args, t_data *data);
int		my_export(char **args, t_data *data, int i);

#endif
