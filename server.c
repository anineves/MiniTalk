void	handle_signals(int signum, siginfo_t *info, void *ucontent)
{
	static  int nbits;
	static  char	c;
  
  n=0;
  
	if (nbits < 0)
		bit_itr = 8;
	if (signum == SIGUSR1)
		c |= (1 << bit_itr);
	nbits--;
	if (nbits < 0 && c)
	{
		c = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			handle_errors("failed to send SIGUSR2");
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		handle_errors("Failed to send SIGUSR1");
}

void	config_signals(void)
{
	struct sigaction	sa_sigact;

	sa_sigact.sa_sigaction = &handle_signals;
	sa_sigact.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_sigact, NULL) == -1)
		handle_errors("SIGUSR1");
	if (sigaction(SIGUSR2, &sa_sigact, NULL) == -1)
		handle_errors("Failed to change SIGUS");
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID = %d\n\", pid);
	config_signals();
}
