/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:53:39 by sav               #+#    #+#             */
/*   Updated: 2023/05/08 11:15:02 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_index(char *str)
{
	int	i;
	int	flag;

	if (!str)
		return (-1);
	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 96)
		{
			if (flag)
				flag = 0;
			else if (!flag)
				flag = 1;
		}
		if (!flag && str[i] == 36)
			return (i);
	}
	return (-1);
}

static char	*find_var_name(char *str, int i)
{
	char	*var_name;
	int		j;
	int		index;

	j = i;
	while (str[j])
	{
		if (!is_printable(str[j]))
			break ;
		j++;
	}
	var_name = ft_calloc(j - i + 1, 1);
	index = 0;
	while (i < j)
	{
		var_name[index] = str[i];
		index++;
		i++;
	}
	return (var_name);

}

static char	*sub_dollar(t_exp *exps, char **env, int i)
{
	char	*new_char;
	char	*var_name;
	char	*var_value;
	char	len;
	int		j;

	var_name = find_var_name(exps->exp, i);
	var_value = find_var_value(exps->exp, info, i);
	if (!var_value)
		var_value = " ";
	len = ft_strlen(var_value) + ft_strlne(exps->exp) - ft_strlne(var_name); // check if right //
	new_char = ft_calloc(len, 1);
	j = 0;
	while (j < i)
	{
		new_char[j] = exps->exp[i];
		j++;
	}
	i = 0;
	while (var_value[i])
	{
		new_char[j] =
	}
	free(var_name);
	free(var_value);

}

void	ft_expand_dollar(t_node *node, t_info *info)
{
	char	*str;
	t_exp	*exps;
	int		i;

	exps = node->exps;
	while (exps)
	{
		while (1)
		{
			i = find_index(exps->exp);
			if (i < 0)
				break ;
			exps->exp = sub_dollar(exps, info->env, i);
		}			
		exps = exps->next;
	}
}
