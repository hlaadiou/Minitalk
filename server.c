/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:43:21 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/28 11:27:10 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	g_character;

int	power(int base, int exponent)
{
	int	result;

	result = 1;
	while (exponent--)
	{
		result *= base;
	}
	return (result);
}

void	set_bits(unsigned char *character, int bool, int *count, pid_t client)
{
	if (bool == 0)
		(*count)++;
	else
	{
		*character += power(2, *count);
		(*count)++;
	}
	kill(client, SIGUSR1);
}

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int		count;
	static pid_t	pid;

	(void)context;
	if (pid == 0)
		pid = inf->si_pid;
	if (inf->si_pid != pid)
	{
		g_character = 0;
		count = 0;
		pid = inf->si_pid;
	}
	if (count == 8)
	{
		ft_putchar_fd(g_character, STDOUT_FILENO);
		g_character = 0;
		count = 0;
	}
	if (signal == SIGUSR1)
		set_bits(&g_character, 0, &count, pid);
	else if (signal == SIGUSR2)
		set_bits(&g_character, 1, &count, pid);
}

int	main(void)
{
	struct sigaction	ac;

	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ac.sa_sigaction = signal_handler;
	sigemptyset(&ac.sa_mask);
	ac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &ac, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &ac, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
		pause();
	return (0);
}
