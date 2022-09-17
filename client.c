/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhamel <aalhamel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 02:06:36 by aalhamel          #+#    #+#             */
/*   Updated: 2022/04/09 22:39:01 by aalhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_error(char *error)
{
	while (*error)
		write(1, error++, 1);
	exit(1);
}

int	ft_atoi(const char *c)
{
	size_t	num;
	int		i;
	int		sign;

	i = 0;
	num = 0;
	sign = -1;
	while ((c[i] >= 9 && c[i] <= 13) || c[i] == 32)
		i++;
	if (c[i] == '-' || c[i] == '+')
	{
		if (c[i] == '-')
			sign *= -sign;
		i++;
	}
	while (c[i] > 47 && c[i] < 58 && c[i])
	{
		num *= 10;
		num += (c[i++] - '0');
	}
	if (num > 2147483648 && sign == -1)
		return (0);
	if (num > 2147483647 && sign == 1)
		return (1);
	return ((int)num);
}

int	ft_errorhandler(pid_t pid, char *str)
{
	if (pid <= 0 || pid >= 100000)
		ft_error("invalid PID 12");
	else if (!str)
		ft_error("nothing to send");
	return (1);
}

void	ft_sig2kill(pid_t pid, char *str)
{
	int		i;

	while (*str != '\0')
	{
		i = 7;
		while (i >= 0 && *str)
		{
			if ((*str >> i) & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					ft_error("invalid PID 23");
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					ft_error("invalid PID 34");
			}
			usleep(100);
			i--;
		}
		str++;
	}
}

int	main(int arc, char **arg)
{
	if (arc != 3)
		ft_error("invalid number of arguments");
	else if (!ft_errorhandler(ft_atoi(arg[1]), arg[2]))
		return (0);
	ft_sig2kill(ft_atoi(arg[1]), arg[2]);
	return (0);
}
