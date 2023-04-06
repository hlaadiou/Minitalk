/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:43:16 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/06 00:17:08 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	**input;

int	ft_atoi(const char *str)
{
	int		i;
	int		result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	return (sign * result);
}

// void	extract_bits(char *input, pid_t server_pid)
// {
// 	int	i;
// 	int	bits;

// 	i = 0;
// 	while (input[i])
// 	{
// 		bits = 8;
// 		while (bits)
// 		{
// 			if ((input[i] >> (8 - bits)) & 1)
// 				kill(server_pid, SIGUSR2);
// 			else
// 				kill(server_pid, SIGUSR1);
// 			usleep(1000);
// 			bits--;
// 		}
// 		i++;
// 	}
// }

void	signal_handler(int signal, siginfo_t *inf, void *context)
{
	static int	i;
	static int	bits;

	usleep(100);
	if (!(input[2][i]))
		exit(EXIT_SUCCESS);
	if (bits == 8)
	{
		bits = 0;
		i++;
	}
	if ((input[2][i] >> bits) & 1)
		kill(ft_atoi(input[1]), SIGUSR2);
	else
		kill(ft_atoi(input[1]), SIGUSR1);
	bits++;
}

int	main(int argc, char **argv)
{
	struct sigaction	ac;

	if (argc != 3)
		exit(EXIT_FAILURE);
	input = argv;
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
