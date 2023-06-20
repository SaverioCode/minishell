/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:39:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/20 23:00:31 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(char **args)
{
	char	*cwd;
	char	*buff;
	int		size;

	if (args != NULL)
	{
		write(2, "Error: to many arguments.\n", 26);
		return (1);
	}
	cwd = NULL;
	buff = NULL;
	size = 1;
	while (cwd == NULL)
	{
		free(cwd);
		free(buff);
		buff = ft_calloc(1, size);
		cwd = getcwd(buff, size);
		size++;
	}
	free(buff);
	write(1, cwd, size - 1);
	write(1, "\n", 1);
	return (0);
}
