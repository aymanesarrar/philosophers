/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:52:31 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/30 12:05:11 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_meal(t_philosopher *head)
{
	int	c;
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

int	check_death(t_args *args, t_philosopher *head)
{
	int	meal;
	int	starving;

	if (args->nb_must_eat != 0)
	{
		meal = check_meal(head);
		if (meal)
		{
			pthread_mutex_lock(&args->death_protection);
			return (printf("all philosophers has eaten their meal\n"));
		}
	}
	starving = check_loop(head);
	if (starving)
	{
		pthread_mutex_lock(&args->death_protection);
		return (printf("%d died\n", starving));
	}
	return (0);
}

void	routine_all(t_philosopher *philo, t_philosopher *next)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->args->death_protection);
	printf_pro_max("has taken a fork", philo);
	pthread_mutex_unlock(&philo->args->death_protection);
	pthread_mutex_lock(&next->fork);
	pthread_mutex_lock(&philo->args->death_protection);
	printf_pro_max("is eating", philo);
	pthread_mutex_unlock(&philo->args->death_protection);
	if (philo->args->nb_must_eat != 0)
		philo->meal++;
	philo->last_meal = current_time();
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
		routine_all(philo, next);
	return (NULL);
}
