#include "./philo.h"

long	ft_positive_atoi(char *str)
{
	long	nb;
	int		index;

	nb = 0;
	index = 0;
	while (str[index])
	{
		nb = (nb * 10) + ((int)str[index] - '0');
		index++;
	}
	return (nb);
}