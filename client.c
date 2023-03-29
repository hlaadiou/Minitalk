/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:43:16 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/03/27 10:55:22 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
		exit(EXIT_FAILURE);
}

char	extract_bits(char **input, pid_t server_pid)
{
	int	i;
	int	bits;

	i = 0;
	bits = 8;
	while (input[2][i++])
	{
		while (bits--)
		{
			if ((input[2][i] << (8 - bits)) & 1)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			usleep(100);
		}
	}
}