/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:17:17 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/24 15:47:18 by aysarrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;
}				t_args;

typedef struct s_philosopher
{
	int						index;
	long int				last_meal;
	pthread_mutex_t			fork;
	pthread_t				thread;
	struct s_args			*args;
	struct s_philosophers	*next;
}				t_philosopher;

int			check_number(char *str);
int			check_arguments(char **av);
long		ft_positive_atoi(char *str);
void		ft_usleep(long int time_in_ms);
long int	current_time(void);
void		ft_error(char *str);

#endif