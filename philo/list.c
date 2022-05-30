/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:57:25 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/30 10:59:57 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*create_node(int index, t_args *args)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->index = index;
	if (pthread_mutex_init(&philo->fork, NULL))
		return (printf("error initializing a mutex\n"), NULL);
	if (pthread_mutex_init(&args->printf_protection, NULL))
		return (printf("error initializing a mutex\n"), NULL);
	if (pthread_mutex_init(&args->death_protection, NULL))
		return (printf("error initializing a mutex\n"), NULL);
	philo->args = args;
	philo->next = NULL;
	philo->meal = 0;
	philo->last_meal = 0;
	return (philo);
}

void	add_last(t_philosopher **HEAD, t_philosopher *node)
{
	t_philosopher	*tmp;

	if (!node)
		return ;
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
	t_philosopher	*headd;
	int				index;

	index = 1;
	headd = NULL;
	while (index <= args->nb_philo)
	{
		add_last(&headd, create_node(index, args));
		index++;
	}
	if (!headd)
		return (NULL);
	headd->args->head = headd;
	return (headd);
}

int	printf_pro_max(char *str, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->args->printf_protection);
	printf("%ldms %d %s\n", current_time(), philo->index, str);
	pthread_mutex_unlock(&philo->args->printf_protection);
	return (0);
}
