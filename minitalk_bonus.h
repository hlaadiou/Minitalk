/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 23:13:13 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/04/28 11:32:58 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_bzero(void *b, size_t len);
int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	set_bits(int bool, int *bits, int index, pid_t client);
void	check_bits(int *bytes, int bool, int *u_bits, pid_t client);
void	signal_handler(int signal, siginfo_t *inf, void *context);
void	send_signal(int index, int bits, int signal);

#endif