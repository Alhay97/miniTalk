/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhamel <aalhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:25:46 by aalhamel          #+#    #+#             */
/*   Updated: 2022/04/09 22:37:11 by aalhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnumber(int c)
{
	unsigned int	i;

	i = c;
	if (c < 0)
	{
		ft_putchar('-');
		i = c * -1;
	}
	if (i / 10 != 0)
		ft_putnumber(i / 10);
	ft_putchar(i % 10 + 48);
}

void	ft_signalhandler(int sig)
{
	static int				i;
	static unsigned char	str;

	str |= (sig == SIGUSR2);
	i++;
	if (i == 8)
	{
		ft_putchar(str);
		i = 0;
		str = 0;
	}
	else
		str <<= 1;
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	write(1, "the PID number is: ", 30);
	ft_putnumber(pid);
	ft_putchar('\n');
	signal(SIGUSR1, ft_signalhandler);
	signal(SIGUSR2, ft_signalhandler);
	while (1)
		pause();
	return (0);
}
