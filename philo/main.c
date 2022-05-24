/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:23:38 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/24 23:49:27 by aysarrar         ###   ########.fr       */
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
	philo->last_meal = 0;
	return (philo);
}

void	add_last(t_philosopher **HEAD, t_philosopher *node)
{
	t_philosopher *tmp;

	tmp = *HEAD;
	if (!*HEAD)
	{
		*HEAD = node;
		return ;
	}
	while ((tmp)->next)
		tmp = (tmp)->next;
	(tmp)->next = node;
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
	HEAD->args->head = HEAD;
	return (HEAD);
}

int	printf_pro_max(char *str, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->args->printf_protexion);
	printf("%ldms %d %s\n", current_time(), philo->index, str);
	pthread_mutex_unlock(&philo->args->printf_protexion);
	return (0);
}

void	*routine(void *ptr)
{
	t_philosopher	*philo;
	t_philosopher	*next;

	philo = (t_philosopher *)ptr;
	if (philo->index % 2 == 1)
		ft_usleep(20);
	if (philo->next)
		next = philo->next;
	else
		next = (t_philosopher *)philo->args->head;
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&next->fork);
		pthread_mutex_lock(&philo->args->death_protexion);
		printf_pro_max("is eating", philo);
		philo->last_meal = current_time();
		pthread_mutex_unlock(&philo->args->death_protexion);
		ft_usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&next->fork);
		pthread_mutex_lock(&philo->args->death_protexion);
		printf_pro_max("is sleeping", philo);
		pthread_mutex_unlock(&philo->args->death_protexion);
		ft_usleep(philo->args->time_to_sleep);
	}
	return (NULL);
}

int	create_threads(t_args *args, t_philosopher **HEAD)
{
	t_philosopher 	*tmp;

	*HEAD = create_list(args);
	tmp = *HEAD;
	while (tmp)
	{
		if (pthread_create(&tmp->thread, NULL, routine, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	init(int ac, char **av, t_args *arguments, t_philosopher **head)
{
	arguments->nb_philo = ft_positive_atoi(av[1]);
	arguments->time_to_die = ft_positive_atoi(av[2]);
	arguments->time_to_eat = ft_positive_atoi(av[3]);
	arguments->time_to_sleep = ft_positive_atoi(av[4]);
	if (av[ac])
		arguments->nb_must_eat = ft_positive_atoi(av[5]);
	if (!create_threads(arguments, head))
		return (0);
	return (1);
}

int	check_loop(t_philosopher *head)
{
	while (head)
	{
		if (current_time() - head->last_meal > head->args->time_to_die)
			return (head->index);
		head = head->next;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_args			arguments;
	t_philosopher	*head;
	int				var;

	pthread_mutex_init(&arguments.printf_protexion, NULL);
	pthread_mutex_init(&arguments.death_protexion, NULL);
	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
			return (printf("invalid arguments\n"));
		if (!init(ac, av, &arguments, &head))
			return (printf("Error\n"));
	}
	else
		return (printf("invalid arguments\n"));
	while (1)
	{
		var = check_loop(head);
		if (var)
		{
			pthread_mutex_lock(&arguments.death_protexion);
			return (printf("%d died\n", var));
		}
	}
	return (0);
}