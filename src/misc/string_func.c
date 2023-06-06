/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@42heilbronn.student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 20:28:25 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/06 11:00:21 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

void	str_free(char *s1, char *s2, int id)
{
	if (!id)
		return ;
	if ((id == 1 || id == 3) && s1)
		free(s1);
	if ((id == 2 || id == 3) && s2)
		free(s2);
}

char	*my_strjoin(char *s1, char *s2, int id)
{
	char	*nstring;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	nstring = malloc(my_strlen(s1) + my_strlen(s2) + 1);
	if (!nstring)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		nstring[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		nstring[i] = s2[j];
		i++;
		j++;
	}
	nstring[i] = '\0';
	return (str_free(s1, s2, id), nstring);
}
