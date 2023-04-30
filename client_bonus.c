/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:12:49 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/30 12:14:39 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

char	**g_input;

void	count_bytes(int pos, int *bytes)
{
	char	str;

	str = g_input[2][pos];
	str = str >> 4;
	if ((str & 0b1111) == 0b1111)
		*bytes = 4;
	else if ((str & 0b1110) == 0b1110)
		*bytes = 3;
	else if ((str & 0b1100) == 0b1100)
		*bytes = 2;
	else
		*bytes = 1;
}

void	send_signal(int index, int *bits, int signal)
{
	(void)signal;
	if ((g_input[2][index] >> (*bits)) & 1)
		kill(ft_atoi(g_input[1]), SIGUSR2);
	else
		kill(ft_atoi(g_input[1]), SIGUSR1);
	(*bits)++;
	return ;
}

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int	i;
	static int	bytes;
	static int	bits;
	static int	u_bits;

	(void)inf;
	(void)context;
	usleep(300);
	if (bytes == 0)
		count_bytes(i, &bytes);
	if (bits == 8)
	{
		bits = 0;
		if (g_input[2][i])
			i++;
	}
	if (u_bits == (bytes * 8))
	{
		u_bits = 0;
		count_bytes(i, &bytes);
	}
	send_signal(i, &bits, signal);
	u_bits++;
	if (!(g_input[2][i]) && bits == 8)
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	struct sigaction	ac;

	if (argc != 3 || (ft_atoi(argv[1]) == -1) | (ft_atoi(argv[1]) == 0))
		exit(EXIT_FAILURE);
	g_input = argv;
	ac.sa_sigaction = signal_handler;
	sigemptyset(&ac.sa_mask);
	ac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &ac, NULL) == -1)
		exit(EXIT_FAILURE);
	kill(getpid(), SIGUSR1);
	while (1)
		pause();
	return (0);
}
