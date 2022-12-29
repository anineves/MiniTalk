#include "minitalk.h"

void	send_msg(pid_t pid, char *msg)
{
	int		nbits;
	int	i;
	
	i = 0;
	
	
	while (*msg)
	{
		nbits = 0;
		while (nbits < 8)
		{
			if (msg[i] & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			msg[i] >>= 1;
			nbits++;
			usleep(30);
		}
	}
}

int	ft_atoi(const char *str)
{
	int			res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return (res * signal);
}


int	main(int argc, char **argv)
{
	pid_t		pid_server;
	char	*msg;

	if (argc != 3)
		return 0;
	pid_server = ft_atoi(argv[1]);
	msg = argv[2];
	send_msg(pid_server, msg);
	return (0);
}
