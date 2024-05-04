/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:11:11 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/04 17:23:28 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] == '\0')
		return (1);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	is_int(char *nb)
{
	long int	res;

	res = ft_atol(nb);
	if (!(res >= -2147483648 && res <= 2147483647))
	{
		printf("No need to go beyond an int.\n");
		return (1);
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while (av[i])
	{
		if (is_num(av[i]))
		{
			printf("Arguments must be numeric\n");
			return (1);
		}
		if (ft_atoi(av[i]) < 0)
		{
			printf("Positive values only\n");
			return (1);
		}
		if (is_int(av[i]))
			return (1);
		i++;
	}
	return (0);
}
