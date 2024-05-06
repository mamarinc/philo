/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:28:26 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/06 12:35:00 by mamarinc         ###   ########.fr       */
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

static long int	get_last_meal(t_philo *philo)
{
	long int	value;

	pthread_mutex_lock(&philo->data->life.lock_timer);
	value = philo->data->life.timer;
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	return (value);
}

static void	die_alone(t_philo *philo, long int last_meal)
{
	pthread_mutex_lock(&philo->data->life.lock_timer);
	while ((philo->data->life.timer - last_meal) < philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	pthread_mutex_lock(&philo->data->life.lock_timer);
	print_philo(DEATH, philo);
	pthread_mutex_unlock(&philo->data->life.lock_timer);
}

void	*life(void *philos)
{
	t_philo			*philo;
	long int		last_meal;

	philo = (t_philo *)philos;
	last_meal = get_last_meal(philo);
	if (philo->number % 2 == 0)
		usleep(500);
	if (philo->data->number_of_philosophers == 1)
		die_alone(philo, last_meal);
	pthread_mutex_lock(&philo->data->life.lock_timer);
	while (philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		philo_fork(philo, last_meal);
		philo_take_forks(philo);
		last_meal = get_last_meal(philo);
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
