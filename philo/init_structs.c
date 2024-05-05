/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:06:43 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/05 13:53:26 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_struct(t_data *data)
{
	if (data->time_to_eat == 0)
	{
		printf("They need some time to eat\n");
		return (1);
	}
	if (data->time_to_sleep == 0)
	{
		printf("They need some time to sleep\n");
		return (1);
	}
	if (data->number_of_times_each_philosopher_must_eat == 0)
	{
		printf("No need to eat !\n");
		return (1);
	}
	return (0);
}

int	init_struct(t_data *data, char **av)
{
	data->number_of_philosophers = ft_atoi(av[0]);
	if (data->number_of_philosophers == 0)
	{
		printf("At least one philo needed\n");
		return (1);
	}
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->life.meal_number = 0;
	data->life.stop = 0;
	if (av[4])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (data->time_to_die == 0)
	{
		printf("Let them live just a bit\n");
		return (1);
	}
	data->life.timer = 0;
	pthread_mutex_init(&data->life.lock_timer, NULL);
	return (0);
}

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].data = data;
		philo[i].meals = 0;
		philo[i].number = i + 1;
		philo[i].left_fork.fork = 1;
		pthread_mutex_init(&philo[i].left_fork.lock, NULL);
		if (i != 0)
			philo[i].right_fork = &philo[i - 1].left_fork;
		i++;
	}
	i--;
	philo[0].right_fork = &philo[data->number_of_philosophers - 1].left_fork;
}
