/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:23:00 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/04 17:12:09 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->timer.lock_timer);
	if (philo->data->timer.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		pthread_mutex_lock(&philo->left_fork.lock);	
		pthread_mutex_lock(&philo->right_fork->lock);
		philo->left_fork.fork = 0;
		philo->right_fork->fork = 0;
		pthread_mutex_unlock(&philo->left_fork.lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		print_philo(FORK, philo);
		print_philo(FORK, philo);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->timer.lock_timer);
}

int	philo_fork(t_philo *philo, long int last_meal)
{
	pthread_mutex_lock(&philo->data->timer.lock_timer);
	while ((philo->left_fork.fork == 0 || philo->right_fork->fork == 0 || philo->data->number_of_philosophers == 1)
			&& philo->data->timer.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
		if ((philo->data->timer.timer - last_meal) >= philo->data->time_to_die)
			print_philo(DEATH, philo);
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
	}
	if ((philo->data->timer.timer - last_meal) >= philo->data->time_to_die)
		print_philo(DEATH, philo);
	pthread_mutex_unlock(&philo->data->timer.lock_timer);
	return (0);
}

int	philo_eat(t_philo *philo, long int last_meal)
{
	print_philo(EAT, philo);
	philo->meals++;
	pthread_mutex_lock(&philo->data->timer.lock_timer);
	while (philo->data->timer.timer - last_meal < philo->data->time_to_eat
			&& philo->data->timer.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
		if (philo->data->timer.timer - last_meal >= philo->data->time_to_die)
			print_philo(DEATH, philo);
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->timer.lock_timer);
	return (0);
}

int	finish_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->timer.lock_timer);
	if (philo->data->timer.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		pthread_mutex_lock(&philo->left_fork.lock);
		pthread_mutex_lock(&philo->right_fork->lock);
		philo->left_fork.fork = 1;
		philo->right_fork->fork = 1;
		pthread_mutex_unlock(&philo->left_fork.lock);
		pthread_mutex_unlock(&philo->right_fork->lock);
		if (philo->meals == philo->data->number_of_times_each_philosopher_must_eat)
			philo->data->meal_number++;
		if (philo->data->meal_number == philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->timer.lock_timer);
			philo->data->timer.stop = 2;
			pthread_mutex_unlock(&philo->data->timer.lock_timer);
		}
		pthread_mutex_lock(&philo->data->timer.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->timer.lock_timer);
	return (0);
}

int	philo_sleep(t_philo *philo, long int last_meal)
{
	long int		sleep_time;

	pthread_mutex_lock(&philo->data->timer.lock_timer);
	sleep_time = philo->data->timer.timer;
	pthread_mutex_unlock(&philo->data->timer.lock_timer);
	print_philo(SLEEP, philo);
	pthread_mutex_lock(&philo->data->timer.lock_timer);
	while (philo->data->timer.timer - sleep_time < philo->data->time_to_sleep
			&& philo->data->timer.stop == 0)
	{
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
		if (philo->data->timer.timer - last_meal >= philo->data->time_to_die)
			print_philo(DEATH, philo);
		pthread_mutex_unlock(&philo->data->timer.lock_timer);
		usleep(100);
		pthread_mutex_lock(&philo->data->timer.lock_timer);
	}
	pthread_mutex_unlock(&philo->data->timer.lock_timer);
	return (0);
}
