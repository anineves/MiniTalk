/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 09:44:34 by asousa-n          #+#    #+#             */
/*   Updated: 2022/12/21 09:45:09 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	send_msg(char *str, pid_t p)
{
	int				count;
	unsigned char	c;
	int				bit;
	int				lenstr;

	count = 0;
	lenstr = ft_strlen(str);
	while (count <= lenstr)
	{
		c = (unsigned char) str[count];
		bit = 0;
		while (bit < 8)
		{
			if (c & 0b00000001)
				kill(p, SIGUSR1);
			else
				kill(p, SIGUSR2);
			c >>= 1;
			bit++;
			usleep(30);
		}
		count++;
	}
}

void	handler(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Message received!");
}

void	config_signals(void)
{
	struct sigaction	sa_sigact;

	sa_sigact.sa_handler = &handler;
	sa_sigact.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_sigact, NULL) == -1)
		printf("Error SIGUSR1");
	if (sigaction(SIGUSR2, &sa_sigact, NULL) == -1)
		printf("Error SIGUR2");
}

int	main(int argc, char **argv)
{
	pid_t		pid_server;
	char	*msg;

	if(argc != 3)
	{
		printf("Numero de argumentos invalido \n Por favor insira o pid do cliente e a mensagem");
		return (0);
	}
	pid_server = ft_atoi(argv[1]);
	msg = argv[2];
	send_msg(pid_server, msg);
	while (1)
		pause();
	return (0);
}
