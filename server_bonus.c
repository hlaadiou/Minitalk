/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:13:48 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/26 17:29:36 by hlaadiou         ###   ########.fr       */
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
	{
		// printf("0\n");
		return (0);
	}
	else if ((str & 0b1111) == 0b1111)
	{
		// printf("4\n");
		return (4);
	}
	else if ((str & 0b1110) == 0b1110)
	{
		// printf("3\n");
		return (3);
	}
	else if ((str & 0b1100) == 0b1100)
	{
		// printf("2\n");
		return (2);
	}
	else
	{
		// printf("1\n");
		return (1);
	}
}

// void	set_bits(unsigned char *u_character, int bool, int *bytes, pid_t client)
// {
// 	static int	bits;
// 	static int	i;

// 	if (*bytes == -1)
// 	{
// 		i = 0;
// 		bits = 0;
// 		(*bytes) = 0;
// 	}
// 	if (bits == 8)
// 	{
// 		(*bytes) = count_bytes();
// 		bits = 0;
// 		i++;
// 	}
// 	if (i == (*bytes))
// 	{
// 		ft_putunicode_fd(g_ucharacter, (*bytes), STDOUT_FILENO);
// 		ft_bzero(g_ucharacter, sizeof(g_ucharacter));
// 		i = 0;
// 	}
// 	if (bool == 1)
// 	{
// 		*(u_character + i) = ((1 << bits) | *(u_character + i));
// 		bits++;
// 	}
// 	else
// 	{
// 		bits++;
// 	}
// 	kill(client, SIGUSR1);
// }

void	set_bits(int *bytes, int bool, int *u_bits, pid_t client)
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
	if (bool == 1)
	{
		g_ucharacter[i] = 1 << bits | g_ucharacter[i];
		bits++;
	}
	else
		bits++;
	kill(client, SIGUSR1);
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
		set_bits(&bytes, 0, &u_bits, pid);
		u_bits++;
	}
	else if (signal == SIGUSR2)
	{
		set_bits(&bytes, 1, &u_bits, pid);
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
	{
		pause();
		// printf("%d\n", g_ucharacter[0]);
	}
	return (0);
}
