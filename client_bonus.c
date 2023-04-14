/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:12:49 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/14 01:27:59 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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

void	count_bytes(int pos, int *bytes)
{
	char	str;

	str = input[2][pos];
	str = str >> 4;
	// if (((1 << 3) & str) == 0)
	// 	*bytes = 1;
	if (str == 0b1111)
		*bytes = 4;
	else if (str == 0b1110)
		*bytes = 3;
	else if (str >> 1 == 0b110)
		*bytes = 2;
	else
		*bytes = 1;
}

// void	signal_handler(int signal, siginfo_t *inf, void *context)
// {
// 	static int	i;
// 	static int	bytes;
// 	static int	bits;
// 	static int	u_bits;

// 	usleep(100);
// 	if (!(input[2][i]))
// 		exit(EXIT_SUCCESS);
// 	if (bytes == 0)
// 		count_bytes(i, &bytes);
// 	if (bits == 8)
// 		bits = 0;
// 	if (u_bits == 32)
// 	{
// 		u_bits = 0;
// 		i++;
// 		// count_bytes(i, &bytes);
// 	}
// 	if (u_bits < (8 * bytes))
// 	{
// 		if ((input[2][i] >> bits) & 1)
// 			kill(ft_atoi(input[1]), SIGUSR2);
// 		else
// 			kill(ft_atoi(input[1]), SIGUSR1);
// 		bits++;
// 		u_bits++;
// 	}
// 	else if (u_bits >= (8 * bytes) && u_bits < 32)
// 	{
// 		kill(ft_atoi(input[1]), SIGUSR1);
// 		u_bits++;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	struct sigaction	ac;

// 	if (argc != 3)
// 		exit(EXIT_FAILURE);
// 	input = argv;
// 	ac.sa_sigaction = signal_handler;
// 	sigemptyset(&ac.sa_mask);
// 	ac.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGUSR1, &ac, NULL) == -1)
// 		exit(EXIT_FAILURE);
// 	kill(getpid(), SIGUSR1);
// 	while (1)
// 		pause();
// 	return (0);
// }

int	main(int ac, char **av)
{
	int	bytes = 0;

	input = av;
	count_bytes(0, &bytes);
	printf("%d\n", bytes);
	return (0);
}