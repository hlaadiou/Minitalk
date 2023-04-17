/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:13:48 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/17 00:50:20 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

unsigned char	g_ucharacter[4];

void	ft_memset(unsigned char *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(b + i) = (unsigned char)c;
		i++;
	}
	return ;
}

void	ft_putunicode_fd(unsigned char *c, int size, int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(1, &g_ucharacter[i], sizeof(unsigned char));
		i++;
	}	
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

void	set_bits(unsigned char *u_char, int bool, int *bytes, pid_t client)
{
	static int	bits;
	static int	i;

	if (*bytes == -1)
	{
		i = 0;
		bits = 0;
		(*bytes) = 0;
	}
	if (bits == 8)
	{
		(*bytes) = count_bytes();
		bits = 0;
		i++;
	}
	if (i == (*bytes))
	{
		ft_putunicode_fd(g_ucharacter, (*bytes), STDOUT_FILENO);
		ft_memset(g_ucharacter, 0, sizeof(g_ucharacter));
		i = 0;
	}
	if (bool == 1)
	{
		*(u_char + i) = ((1 << bits) | *(u_char + i));
		bits++;
	}
	else
		bits++;
	kill(client, SIGUSR1);
}

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int		bytes;
	static pid_t	pid;

	if (pid == 0)
		pid = inf->si_pid;
	if (inf->si_pid != pid)
	{
		ft_memset(g_ucharacter, 0, sizeof(g_ucharacter));
		bytes = -1;
		pid = inf->si_pid;
	}
	if (signal == SIGUSR1)
		set_bits(&g_ucharacter, 0, &bytes, pid);
	else if (signal == SIGUSR2)
		set_bits(&g_ucharacter, 1, &bytes, pid);
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
