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

void	send_msg(pid_t p, char *str)
{
	int				count;
	unsigned char	c;
	int				bit;

	count = 0;
	while (str[count] != '\0')
	{
		c = (unsigned char) str[count];
		bit = 8;
		while (bit > 0)
		{
			if (c & 0b00000001)
				kill(p, SIGUSR1);
			else
				kill(p, SIGUSR2);
			c >>= 1;
			bit--;
			usleep(100);
		}
		count++;
	}
}

int	main(int argc, char **argv)
{
	pid_t		pid_server;
	char		*msg;

	if (argc != 3)
	{
		ft_printf("invalid arguments");
		return (0);
	}
	pid_server = ft_atoi(argv[1]);
	msg = argv[2];
	send_msg(pid_server, msg);
	return (0);
}
