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

void	handler_signals(int signal, siginfo_t *info, void *ucontent)
{
	static int				i = 0;
	static unsigned char	c = 0;
	
	(void)ucontent;
	if (i < 0)
		i = 7;
	if (signal == SIGUSR1)
		c =  c | (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_printf(");
			kill (info->si_pid, SIGUSR1);
		}
		i = 0;
		c = 0; 
	}
	
}

void	config_signals(void)
{
	struct sigaction	sa_sigact;

	sa_sigact.sa_sigaction = &handler_signals;
	sa_sigact.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_sigact, NULL) == -1)
		printf("Error SIGUSR1");
	if (sigaction(SIGUSR2, &sa_sigact, NULL) == -1)
		printf("Error SIGUR2");
}

int	main(void)
{
	pid_t	pid;
	
	pid = getpid();
	ft_printf("PID = %d\n", pid);
	config_signals();
	while (1)
		config_signals();
	return (0);
}
