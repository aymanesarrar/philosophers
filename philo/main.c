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

void	init(int ac, char **av)
{
	t_args arguments;

	arguments.nb_philo = ft_positive_atoi(av[1]);
	arguments.time_to_die = ft_positive_atoi(av[2]);
	arguments.time_to_eat = ft_positive_atoi(av[3]);
	arguments.time_to_sleep = ft_positive_atoi(av[4]);
	if (av[ac])
		arguments.nb_must_eat = ft_positive_atoi(av[5]);
	ft_usleep(2000);
	
}

int main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
		{
			printf("invalid arguments\n");
			return (1);
		} 
		init(ac, av);
	}
	else
		printf("invalid arguments\n");
	return (0);
}