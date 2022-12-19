void	send_msg(int pid, char *msg, size_t len_msg)
{
	int		nbit;
	size_t	i;

	i = 0;
	while (i <= len_msg)
	{
		nbit = 0;
		while (shift < 7)
		{
			if ((msg[i] >> nbit) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			nbit++;
			usleep(300);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid_server;
	char	*msg;
	size_t len_msg;


	if (argc == 3)
	{
		pid_server = ft_atoi(argv[1]);
		msg = argv[2];
		len_msg = ft_strlen(msg);
		send_msg(pid, msg, len_msg);
	}
}
