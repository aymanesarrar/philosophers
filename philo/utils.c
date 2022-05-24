/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:14:32 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/24 22:43:15 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_error(char *str)
{
	printf("%s\n", str);
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
	long int			time;
	struct timeval		current_time;
	static	long int	begin_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		ft_error("Error\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	if (!begin_time)
		begin_time = time;
	return (time - begin_time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
		usleep(50);
}
