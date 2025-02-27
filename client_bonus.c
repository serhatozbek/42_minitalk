/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sozbek <sozbek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:07:14 by sozbek            #+#    #+#             */
/*   Updated: 2025/02/28 00:56:55 by sozbek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int		g_signal_received = 0;

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

int	ft_atoi(const char *str)
{
	int	a;
	int	i;
	int	result;

	i = 0;
	a = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * a);
}

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_signal_received = 1;
	else if (signal == SIGUSR2)
	{
		ft_putstr("\nMessage arrived.\n");
		exit(1);
	}
}

void	ft_transfer(char c, int pid)
{
	int	i;
	int	check;

	check = 0;
	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			check = kill(pid, SIGUSR1);
		else
			check = kill(pid, SIGUSR2);
		if (check == -1)
		{
			ft_putstr("ERROR: Kill error !");
			exit(1);
		}
		i--;
		while (!g_signal_received)
			pause();
		g_signal_received = 0;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	server_pid;

	i = 0;
	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]);
		if (server_pid <= 0)
		{
			ft_putstr("PID error !\n");
			return (0);
		}
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		while (av[2][i])
			ft_transfer(av[2][i++], server_pid);
	}
	else
	{
		ft_putstr("Error: Arguman count error !");
		return (0);
	}
	ft_transfer(server_pid, '\0');
	return (0);
}
