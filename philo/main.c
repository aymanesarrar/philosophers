/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:23:38 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/30 10:57:16 by aysarrar         ###   ########.fr       */
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

int	create_threads(t_args *args, t_philosopher **HEAD)
{
	t_philosopher	*tmp;

	*HEAD = create_list(args);
	tmp = *HEAD;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (pthread_create(&tmp->thread, NULL, routine, tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	init(char **av, t_args *arguments, t_philosopher **head)
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

int	main(int ac, char **av)
{
	t_args			arguments;
	t_philosopher	*head;

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
		if (check_death(&arguments, head))
			break ;
	}
	return (0);
}
