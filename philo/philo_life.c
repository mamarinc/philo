/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:23:00 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/05 14:05:59 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->life.lock_timer);
	if (philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->right_fork->lock);
		pthread_mutex_lock(&philo->left_fork.lock);
		philo->left_fork.fork = 0;
		philo->right_fork->fork = 0;
		pthread_mutex_unlock(&philo->left_fork.lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		print_philo(FORK, philo);
		print_philo(FORK, philo);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
}

int	philo_fork(t_philo *philo, long int last_meal)
{
	pthread_mutex_lock(&philo->data->life.lock_timer);
	while ((philo->left_fork.fork == 0 || philo->right_fork->fork == 0
			|| philo->data->number_of_philosophers == 1)
		&& philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		if ((philo->data->life.timer - last_meal) >= philo->data->time_to_die)
			print_philo(DEATH, philo);
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	pthread_mutex_lock(&philo->data->life.lock_timer);
	if ((philo->data->life.timer - last_meal) >= philo->data->time_to_die)
		print_philo(DEATH, philo);
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	return (0);
}

int	philo_eat(t_philo *philo, long int last_meal)
{
	print_philo(EAT, philo);
	philo->meals++;
	pthread_mutex_lock(&philo->data->life.lock_timer);
	while (philo->data->life.timer - last_meal < philo->data->time_to_eat
		&& philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		if (philo->data->life.timer - last_meal >= philo->data->time_to_die)
			print_philo(DEATH, philo);
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	return (0);
}

int	finish_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->life.lock_timer);
	if (philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->right_fork->lock);
		pthread_mutex_lock(&philo->left_fork.lock);
		philo->left_fork.fork = 1;
		philo->right_fork->fork = 1;
		pthread_mutex_unlock(&philo->left_fork.lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		if (philo->meals
			== philo->data->number_of_times_each_philosopher_must_eat)
			philo->data->life.meal_number++;
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		if (philo->data->life.meal_number
			== philo->data->number_of_philosophers)
			philo->data->life.stop = 2;
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	return (0);
}

int	philo_sleep(t_philo *philo, long int last_meal)
{
	long int		sleep_time;

	pthread_mutex_lock(&philo->data->life.lock_timer);
	sleep_time = philo->data->life.timer;
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	print_philo(SLEEP, philo);
	pthread_mutex_lock(&philo->data->life.lock_timer);
	while (philo->data->life.timer - sleep_time < philo->data->time_to_sleep
		&& philo->data->life.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		pthread_mutex_lock(&philo->data->life.lock_timer);
		if (philo->data->life.timer - last_meal >= philo->data->time_to_die)
			print_philo(DEATH, philo);
		pthread_mutex_unlock(&philo->data->life.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->life.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->life.lock_timer);
	print_philo(THINK, philo);
	return (0);
}
