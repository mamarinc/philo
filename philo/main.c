/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:24:25 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/04 17:28:08 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	manage_threads(pthread_t *th, t_philo *philo, t_data *data, int i)
{
	pthread_create(&th[data->number_of_philosophers], NULL, timer, data);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&th[i], NULL, life, &philo[i]);
		i++;
	}
	i = 0;
	while (i <= data->number_of_philosophers)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	if (data->timer.stop == 1)
		printf("Fail.\n");
	else
		printf("All philosophers have eaten well !\n");
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].left_fork.lock);
		i++;
	}
	pthread_mutex_destroy(&data->timer.lock_timer);
}

static void	start_philo(t_data *data)
{
	pthread_t		*th;
	t_philo			*philo;

	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (philo == NULL)
		return ;
	th = malloc(sizeof(pthread_t) * (data->number_of_philosophers + 1));
	if (th == NULL)
	{
		free(philo);
		return ;
	}
	init_philo(philo, data);
	manage_threads(th, philo, data, 0);
	free(th);
	free(philo);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (check_args(ac, av + 1))
		return (1);
	if (init_struct(&data, av + 1))
		return (1);
	if (check_struct(&data))
		return (1);
	start_philo(&data);
}
