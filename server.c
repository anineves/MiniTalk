#include "minitalk.h"
#include <stdio.h>

void	handle_signals(int signal)
{
	static int				i = 0;
	static unsigned char	c = 0;


	if(signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		i = 0;
	}
}


/* void	handle_signals(int signum, siginfo_t *info, void *ucontent)
{
	static int				bit_itr = -1;
	static unsigned char	c;

	(void)ucontent;
	if (bit_itr < 0)
		bit_itr = 7;
	if (signum == SIGUSR1)
		c |= (1 << bit_itr);
	bit_itr--;
	if (bit_itr < 0 && c)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			printf("Failed SIGUSR2");
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		printf("Failed SIGUSR1");
}
*/

void	config_signals(void)
{
	struct sigaction	sa_sigact;

	sa_sigact.sa_handler = &handle_signals;
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
	printf("PID = %d\n", pid);
	config_signals();
	while (1)
		pause();
	return (0);
}
