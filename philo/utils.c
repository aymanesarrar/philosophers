/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:14:32 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/23 21:21:58 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_error(char *str)
{
	perror(str);
	exit(0);
}

long	ft_positive_atoi(char *str)
{
	long	nb;
	int		index;

	nb = 0;
	index = 0;
	while (str[index])
	{
		nb = (nb * 10) + ((int)str[index] - '0');
		index++;
	}
	return (nb);
}

long int	current_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_error("Error\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
