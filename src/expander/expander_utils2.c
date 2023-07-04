/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:48:42 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/04 16:48:45 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_helper(char *str, t_expdata *exp, int s)
{
	if (!exp->count && exp->i && str[exp->i - 1] == '$')
		exp->sub = get_sub(ft_substr(str, s, exp->i - s - 1), exp);
	else if (!exp->count)
		exp->sub = get_sub(ft_substr(str, s, exp->i - s), exp);
	else if (exp->count == 1)
		exp->sub = get_sub(ft_substr(str, s, exp->i - s + 1), exp);
	return (exp->start);
}
