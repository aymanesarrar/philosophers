/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:23:38 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/23 21:51:49 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_number(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!(str[index] >= '0' && str[index] <= '9'))
			return (0);
		index++;
	}
	return (1);
}

int	check_arguments(char **av)
{
	int	index;

	index = 1;
	while (av[index])
	{
		if (check_number(av[index]) == 0)
			return (0);
		index++;
	}
	return (1);
}

void	*routine()
{
	ft_usleep(200);
	printf("hello from thread\n");
	return (NULL);
}

void	create_philosophers(t_args *args)
{
	int			index;
	pthread_t	philo[args->nb_philo];
	int			thread_return;

	index = 0;
	while (index < args->nb_philo)
	{
		thread_return = pthread_create(&philo[index], NULL, routine, NULL);
		index++;
	}
}

void	init(int ac, char **av)
{
	t_args arguments;

	arguments.nb_philo = ft_positive_atoi(av[1]);
	arguments.time_to_die = ft_positive_atoi(av[2]);
	arguments.time_to_eat = ft_positive_atoi(av[3]);
	arguments.time_to_sleep = ft_positive_atoi(av[4]);
	if (av[ac])
		arguments.nb_must_eat = ft_positive_atoi(av[5]);
	create_philosophers(&arguments);	
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
			ft_error("invalid arguments");
		init(ac, av);
	}
	else
		ft_error("invalid arguments");
	return (0);
}