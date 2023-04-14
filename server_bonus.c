/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:13:48 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/12 18:29:03 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

unsigned int	g_ucharacter;

void	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	set_bits(unsigned int *u_char, int bool, int *count, pid_t client)
{
	if (bool == 1)
	{
		(*u_char) = ((1 << *count) | (*u_char));
		(*count)++;
	}
	else
		(*count)++;
	kill(client, SIGUSR1);
}

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int		count;
	static pid_t	pid;

	if (pid == 0)
		pid = inf->si_pid;
	if (inf->si_pid != pid)
	{
		g_ucharacter = 0;
		count = 0;
		pid = inf->si_pid;
	}
	if (count == 32)
	{
		ft_putchar_fd(g_ucharacter, STDOUT_FILENO);
		g_ucharacter = 0;
		count = 0;
	}
	if (signal == SIGUSR1)
		set_bits(&g_ucharacter, 0, &count, pid);
	else if (signal == SIGUSR2)
		set_bits(&g_ucharacter, 1, &count, pid);
}

int	main(void)
{
	struct sigaction	ac;

	printf("%d\n", getpid());
	ac.sa_sigaction = signal_handler;
	sigemptyset(&ac.sa_mask);
	ac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &ac, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &ac, NULL) == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		pause();
	}
	return (0);
}
