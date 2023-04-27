/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:13:48 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/27 20:30:56 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

unsigned char	g_ucharacter[4];

void	ft_bzero(void *b, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)(b + i) = 0;
		i++;
	}
	return ;
}

void	ft_putunicode_fd(unsigned char *c, int size, int fd)
{
	write(fd, g_ucharacter, size);
	return ;
}

int	count_bytes(void)
{
	unsigned char	str;

	str = g_ucharacter[0];
	str = str >> 4;
	if (g_ucharacter[0] == 0)
		return (0);
	else if ((str & 0b1111) == 0b1111)
		return (4);
	else if ((str & 0b1110) == 0b1110)
		return (3);
	else if ((str & 0b1100) == 0b1100)
		return (2);
	else
		return (1);
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
		(*bytes) = count_bytes();
	if (bits == 8)
	{
		bits = 0;
		i++;
	}
	if ((*u_bits) == ((*bytes) * 8))
	{
		i = 0;
		(*u_bits) = 0;
		ft_putunicode_fd(g_ucharacter, (*bytes), STDOUT_FILENO);
		ft_bzero(g_ucharacter, sizeof(g_ucharacter));
	}
	set_bits(bool, &bits, i, client);
}

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int		bytes;
	static int		u_bits;
	static pid_t	pid;

	if (pid == 0)
		pid = inf->si_pid;
	if (inf->si_pid != pid)
	{
		ft_bzero(g_ucharacter, sizeof(g_ucharacter));
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
		pause();
	return (0);
}
