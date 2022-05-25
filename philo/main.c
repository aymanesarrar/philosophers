/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:23:38 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/25 11:52:47 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int check_number(char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (!(str[index] >= '0' && str[index] <= '9'))
			return (0);
		index++;
	}
	return (1);
}

int check_arguments(char **av)
{
	int index;

	index = 1;
	while (av[index])
	{
		if (check_number(av[index]) == 0)
			return (0);
		index++;
	}
	return (1);
}

t_philosopher *create_node(int index, t_args *args)
{
	t_philosopher *philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->index = index;
	if (pthread_mutex_init(&philo->fork, NULL))
		ft_error("Error initializing mutex\n");
	philo->args = args;
	philo->next = NULL;
	philo->meal = 0;
	philo->last_meal = 0;
	return (philo);
}

void add_last(t_philosopher **HEAD, t_philosopher *node)
{
	t_philosopher *tmp;

	tmp = *HEAD;
	if (!*HEAD)
	{
		*HEAD = node;
		return;
	}
	while ((tmp)->next)
		tmp = (tmp)->next;
	(tmp)->next = node;
}

t_philosopher *create_list(t_args *args)
{
	t_philosopher *HEAD;
	int index;

	index = 1;
	while (index <= args->nb_philo)
	{
		add_last(&HEAD, create_node(index, args));
		index++;
	}
	HEAD->args->head = HEAD;
	return (HEAD);
}

int printf_pro_max(char *str, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->args->printf_protection);
	printf("%ldms %d %s\n", current_time(), philo->index, str);
	pthread_mutex_unlock(&philo->args->printf_protection);
	return (0);
}

void *routine(void *ptr)
{
	t_philosopher *philo;
	t_philosopher *next;

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
		pthread_mutex_lock(&philo->args->death_protection);
		printf_pro_max("has taken a fork", philo);
		pthread_mutex_unlock(&philo->args->death_protection);
		pthread_mutex_lock(&philo->args->death_protection);
		printf_pro_max("is eating", philo);
		if (philo->args->nb_must_eat != 0)
			philo->meal++;
		philo->last_meal = current_time();
		pthread_mutex_unlock(&philo->args->death_protection);
		ft_usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&next->fork);
		pthread_mutex_lock(&philo->args->death_protection);
		printf_pro_max("is sleeping", philo);
		pthread_mutex_unlock(&philo->args->death_protection);
		ft_usleep(philo->args->time_to_sleep);
		pthread_mutex_lock(&philo->args->death_protection);
		printf_pro_max("is thinking", philo);
		pthread_mutex_unlock(&philo->args->death_protection);
	}
	return (NULL);
}

int create_threads(t_args *args, t_philosopher **HEAD)
{
	t_philosopher *tmp;

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

int init(char **av, t_args *arguments, t_philosopher **head)
{
	arguments->nb_philo = ft_positive_atoi(av[1]);
	arguments->time_to_die = ft_positive_atoi(av[2]);
	arguments->time_to_eat = ft_positive_atoi(av[3]);
	arguments->time_to_sleep = ft_positive_atoi(av[4]);
	if (av[5])
		arguments->nb_must_eat = ft_positive_atoi(av[5]);
	else
		arguments->nb_must_eat = 0;
	if (!create_threads(arguments, head))
		return (0);
	return (1);
}

int check_loop(t_philosopher *head)
{
	while (head)
	{
		if (current_time() - head->last_meal > head->args->time_to_die)
			return (head->index);
		head = head->next;
	}
	return (0);
}

int check_meal(t_philosopher *head)
{
	int c;
	int	nb_of_philo;

	c = 0;
	nb_of_philo = head->args->nb_philo;
	while (head)
	{
		if (head->meal >= head->args->nb_must_eat)
			c++;
		head = head->next;
	}
	return (c == nb_of_philo);
}

int main(int ac, char **av)
{
	t_args arguments;
	t_philosopher *head;
	int var;
	int meal;

	if (pthread_mutex_init(&arguments.printf_protection, NULL))
		return (printf("error initializing a mutex\n"));
	if (pthread_mutex_init(&arguments.death_protection, NULL))
		return (printf("error initializing a mutex\n"));
	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
			return (printf("invalid arguments\n"));
		if (!init(av, &arguments, &head))
			return (printf("Error\n"));
	}
	else
		return (printf("invalid arguments\n"));
	while (1)
	{
		var = check_loop(head);
		if (arguments.nb_must_eat != 0)
		{
			meal = check_meal(head);
			if (meal)
			{
				pthread_mutex_lock(&arguments.death_protection);
				return (printf("all philosophers has eaten their meal\n"));
			}
		}
		if (var)
		{
			pthread_mutex_lock(&arguments.death_protection);
			return (printf("%d died\n", var));
		}
	}
	return (0);
}