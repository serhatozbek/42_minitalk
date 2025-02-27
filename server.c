/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sozbek <sozbek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:51 by sozbek            #+#    #+#             */
/*   Updated: 2025/02/24 18:42:49 by sozbek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putpid(int server_pid)
{
	if (server_pid > 9)
		ft_putpid(server_pid / 10);
	write(1, &"0123456789"[server_pid % 10], 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	server_signal(int signal, siginfo_t *info, void *context)
{
	static char	a = 0;
	static int	i = 0;
	int			check;

	check = 0;
	(void)context;
	if (signal == SIGUSR1)
		a = a << 1 | 1;
	else
		a = a << 1;
	i++;
	if (i == 8)
	{
		write(1, &a, 1);
		a = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
	if (check == -1)
	{
		ft_putstr("ERROR: Kill error !");
		exit(1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = server_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_putpid(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
