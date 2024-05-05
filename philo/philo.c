/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:26 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/05 13:53:03 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(char *str, t_philo *philo)
{
	if (!ft_strcmp(str, DEATH))
		pthread_mutex_unlock(&philo->data->life.lock_timer);
	pthread_mutex_lock(&philo->data->life.lock_timer);
	if (philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		if (!ft_strcmp(str, DEATH))
			philo->data->life.stop = 1;
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		printf(str, philo->data->life.timer, philo->number);
	}
	if (ft_strcmp(str, DEATH))
		pthread_mutex_unlock(&philo->data->life.lock_timer);
}

void	*life(void *philos)
{
	t_philo			*philo;
	long int		last_meal;

	philo = (t_philo *)philos;
	pthread_mutex_lock(&philo->data->life.lock_timer);
	last_meal = philo->data->life.timer;
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	if (philo->number % 2 == 0)
		usleep(500);
	pthread_mutex_lock(&philo->data->life.lock_timer);
	while (philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		philo_fork(philo, last_meal);
		philo_take_forks(philo);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		last_meal = philo->data->life.timer;
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		philo_eat(philo, last_meal);
		finish_eating(philo);
		philo_sleep(philo, last_meal);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	return (NULL);
}

void	*timer(void *data_philo)
{
	struct timeval	time;
	t_data			*data;
	long int		new_time;
	long int		old_time;

	data = (t_data *)data_philo;
	gettimeofday(&time, NULL);
	old_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&time, NULL);
		new_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		pthread_mutex_lock(&data->life.lock_timer);
		data->life.timer = new_time - old_time;
		if (data->life.stop != 0)
		{
			pthread_mutex_unlock(&data->life.lock_timer);
			return (NULL);
		}
		pthread_mutex_unlock(&data->life.lock_timer);
		usleep(100);
	}
	return (NULL);
}
