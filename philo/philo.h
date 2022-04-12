#ifndef PHILO_H
#define PHILO_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_args
{
	int	number_of_philosophers; // number of philosophers also number of forks
	int	time_to_die; // if a philosopher didn't start eating time_to_die milliseconds of their last meal or the beginning of the simulation they die
	int	time_to_eat; // the time it takes for a philosopher to eat, during that time they will need to hold 2 forks
	int	time_to_sleep; // the time a philosopher will spend sleeping
	int	nb_must_eat; // if all philosophers have eaten at least nb_must_eat times, the simulation stops, if not specified, the simulation stops when a philosopher dies
}				t_args;

int check_number(char *str);
int check_arguments(char **av);
long ft_positive_atoi(char *str);

#endif