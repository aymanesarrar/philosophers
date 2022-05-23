#ifndef PHILO_H
#define PHILO_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_args
{
	int	nb_philo; // number of philosophers also number of forks
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;
}				t_args;

int check_number(char *str);
int check_arguments(char **av);
long ft_positive_atoi(char *str);

#endif