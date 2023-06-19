/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_termios.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:02:06 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/19 23:33:37 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_set_termios(void)
{
	struct termios	settings;
	int				fd;

	fd = ttyslot();
	if (tcgetattr(fd, &settings) != 0)
	{
		write(1, "ERROR\n", 6);
		exit(1);
	}
	
	settings.c_cc[VINTR] = 4;
	settings.c_cc[VEOF] = 3;
	if (tcsetattr(fd, TCSANOW, &settings) != 0)
	{
		write(1, "ERROR2\n", 7);
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
}
