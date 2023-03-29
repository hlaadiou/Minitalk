/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:43:21 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/03/28 18:42:40 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	g_character;

int	power(int base, int exponent)
{
	int	result;

	result = 1;
	while (exponent--)
	{
		result *= base;
	}
	return (result);
}

void	set_bits(char character, int bool, int *count)
{
	if (bool == 0)
		(*count)++;
	else
	{
		character += (bool * power(2, *count));
		(*count)++;
	}
}

void	signal_handler(int signal)
{
	static int	count;

	if (signal == SIGUSR1)
		set_bits(g_character, 0, &count);
	else if (signal == SIGUSR2)
		set_bits(g_character, 1, &count);
}

int	main(void)
{
	int	counter;

	printf("%d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
	{
		counter = 8;
		while (counter)
		{
			pause();
			counter--;
		}
		printf("%c\n", g_character);
		g_character = 0;
	}
	printf("%d\n", power(0, 0));
	return (0);
}