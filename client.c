#include "minitalk.h"

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
			usleep(30);
		}
		count++;
	}
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
	return (0);
}
