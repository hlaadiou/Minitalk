/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:43:16 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/29 11:51:09 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	**g_input;

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int	i;
	static int	bits;

	(void)context;
	(void)inf;
	(void)signal;
	usleep(300);
	if (!(g_input[2][i]))
		exit(EXIT_SUCCESS);
	if (bits == 8)
	{
		bits = 0;
		i++;
	}
	if ((g_input[2][i] >> bits) & 1)
		kill(ft_atoi(g_input[1]), SIGUSR2);
	else
		kill(ft_atoi(g_input[1]), SIGUSR1);
	bits++;
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
