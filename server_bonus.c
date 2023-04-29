/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:13:48 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/29 21:44:29 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

unsigned char	g_ucharacter[4];

void	count_bytes(int *bytes)
{
	unsigned char	str;

	str = g_ucharacter[0];
	str = str >> 4;
	if (g_ucharacter[0] == 0)
		(*bytes) = 0;
	else if ((str & 0b1111) == 0b1111)
		(*bytes) = 4;
	else if ((str & 0b1110) == 0b1110)
		(*bytes) = 3;
	else if ((str & 0b1100) == 0b1100)
		(*bytes) = 2;
	else
		(*bytes) = 1;
}

void	set_bits(int bool, int *bits, int index, pid_t client)
{
	if (bool == 1)
	{
		g_ucharacter[index] = 1 << (*bits) | g_ucharacter[index];
		(*bits)++;
	}
	else
		(*bits)++;
	kill(client, SIGUSR1);
	return ;
}

void	check_bits(int *bytes, int bool, int *u_bits, pid_t client)
{
	static int	bits;
	static int	i;

	if ((*bytes) == -1)
	{
		i = 0;
		bits = 0;
		(*u_bits) = 0;
		(*bytes) = 0;
	}
	if ((*u_bits) == 8)
		count_bytes(bytes);
	if (bits == 8)
	{
		bits = 0;
		i++;
	}
	if ((*u_bits) == ((*bytes) * 8))
	{
		i = 0;
		(*u_bits) = 0;
		write(STDOUT_FILENO, g_ucharacter, (*bytes));
		ft_bzero(g_ucharacter, sizeof(g_ucharacter), 0);
	}
	set_bits(bool, &bits, i, client);
}

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int		bytes;
	static int		u_bits;
	static pid_t	pid;

	(void)context;
	if (pid == 0)
		pid = inf->si_pid;
	if (inf->si_pid != pid)
	{
		ft_bzero(g_ucharacter, sizeof(g_ucharacter), 1);
		pid = inf->si_pid;
		bytes = -1;
	}
	if (signal == SIGUSR1)
	{
		check_bits(&bytes, 0, &u_bits, pid);
		u_bits++;
	}
	else if (signal == SIGUSR2)
	{
		check_bits(&bytes, 1, &u_bits, pid);
		u_bits++;
	}
	if (u_bits == 8 && g_ucharacter[0] == '\0')
		ft_putstr_fd("\nDONE!", STDOUT_FILENO);
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
