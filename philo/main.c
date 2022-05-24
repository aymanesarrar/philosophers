/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:23:38 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/24 16:11:39 by aysarrar         ###   ########.fr       */
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

t_philosopher	*create_node(int	index, t_args *args)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->index = index;
	if (pthread_mutex_init(&philo->fork, NULL))
		ft_error("Error initializing mutex\n");
	philo->args = args;
	philo->next = NULL;
}

void	add_last(t_philosopher **HEAD, t_philosopher *node)
{
	if (!*HEAD)
	{
		*HEAD = node;
		return ;
	}
	while ((*HEAD)->next)
		HEAD = (*HEAD)->next;
	(*HEAD)->next = node;
}

t_philosopher	*create_list(t_args *args)
{
	t_philosopher 	*HEAD;
	int				index;

	index = 1;
	while (index <= args->nb_philo)
	{
		add_last(&HEAD, create_node(index, args));
		index++;
	}
	return (HEAD);
}

void	*routine(void *args)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)args;
}

int	create_threads(t_args *args)
{
	t_philosopher 	*tmp;
	t_philosopher	*HEAD;

	HEAD = create_list(args);
	tmp = HEAD;
	while (tmp->next)
	{
		if (pthread_create(&tmp->thread, NULL, routine, tmp))
			return (0);
		tmp = tmp->next;
	}
	
}


int	init(int ac, char **av)
{
	t_args arguments;

	arguments.nb_philo = ft_positive_atoi(av[1]);
	arguments.time_to_die = ft_positive_atoi(av[2]);
	arguments.time_to_eat = ft_positive_atoi(av[3]);
	arguments.time_to_sleep = ft_positive_atoi(av[4]);
	if (av[ac])
		arguments.nb_must_eat = ft_positive_atoi(av[5]);
	if (!create_threads(&arguments))
		return (0);
	return (1);	
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
			return (printf("invalid arguments\n"));
		if (!init(ac, av))
			return (printf("Error\n"));
	}
	else
		return (printf("invalid arguments\n"));
	return (0);
}