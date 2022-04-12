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

int main(int ac, char **av)
{
	//t_args	arguments;
	if (ac == 5 || ac == 6)
	{
		if (!check_arguments(av))
		{
			printf("invalid arguments\n");
			return (1);
		} 
	}
	else
		printf("invalid arguments\n");
	return (0);
}