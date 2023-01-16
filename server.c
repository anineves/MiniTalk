/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 09:45:51 by asousa-n          #+#    #+#             */
/*   Updated: 2022/12/21 10:25:34 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	handler_signals(int signal)
{
	static int				i = 0;
	static unsigned char	c = 0;

	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		i = 0;
	}
}

void	config_signals(void)
{
	struct sigaction	sa_sigact;

	sa_sigact.sa_handler = &handler_signals;
	sa_sigact.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_sigact, NULL) == -1)
		ft_printf("Error SIGUSR1");
	if (sigaction(SIGUSR2, &sa_sigact, NULL) == -1)
		ft_printf("Error SIGUR2");
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("PID = %d\n", pid);
	config_signals();
	while (1)
		pause();
	return (0);
}
