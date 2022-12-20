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

void	config_signals(void)
{
	struct sigaction	sa_nsigact;

	sa_nsigact.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_nsigact, NULL) == -1)
		handle_errors("Failed SIGUSR1");
	if (sigaction(SIGUSR2, &sa_nsigact, NULL) == -1)
		handle_errors("Failed SIGUSR2");
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
		config_signals();
		len_msg = ft_strlen(msg);
		send_msg(pid, msg, len_msg);
	}
	else{
		ft_printf("Error");
		
	}
}
