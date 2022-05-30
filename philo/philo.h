/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aysarrar <aysarrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:17:17 by aysarrar          #+#    #+#             */
/*   Updated: 2022/05/30 10:58:13 by aysarrar         ###   ########.fr       */
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
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	void			*head;
	pthread_mutex_t	printf_protection;
	pthread_mutex_t	death_protection;
}				t_args;

typedef struct s_philosopher
{
	int						index;
	long int				last_meal;
	pthread_mutex_t			fork;
	pthread_t				thread;
	int						meal;
	struct s_args			*args;
	struct s_philosopher	*next;
}				t_philosopher;

int				check_number(char *str);
int				check_arguments(char **av);
long			ft_positive_atoi(char *str);
void			ft_usleep(long int time_in_ms);
long int		current_time(void);
int				check_loop(t_philosopher *head);
int				check_meal(t_philosopher *head);
int				check_death(t_args *args, t_philosopher *head);
int				printf_pro_max(char *str, t_philosopher *philo);
void			routine_all(t_philosopher *philo, t_philosopher *next);
void			*routine(void *ptr);
t_philosopher	*create_node(int index, t_args *args);
void			add_last(t_philosopher **HEAD, t_philosopher *node);
t_philosopher	*create_list(t_args *args);

#endif