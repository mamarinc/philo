/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamarinc <mamarinc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:27:12 by mamarinc          #+#    #+#             */
/*   Updated: 2024/05/04 17:33:06 by mamarinc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

# define FORK	"%ld %d has taken a fork\n"
# define EAT	"%ld %d is eating\n"
# define SLEEP	"%ld %d is sleeping\n"
# define THINK	"%ld %d is thinking\n"
# define DEATH	"%ld %d died\n"

typedef struct s_timer
{
	long int		timer;
	int				stop;
	pthread_mutex_t	lock_timer;

}				t_timer;

typedef struct s_data
{
	t_timer			timer;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				meal_number;
}				t_data;

typedef struct s_forks
{
	int				fork;
	pthread_mutex_t	lock;

}				t_forks;

typedef struct s_philo
{
	t_data			*data;
	t_forks			left_fork;
	t_forks			*right_fork;
	int				number;
	int				meals;

}				t_philo;

long int	ft_atol(char *str);
int			ft_atoi(char *str);
int			check_args(int ac, char **av);
int			init_struct(t_data *data, char **av);
void		init_philo(t_philo *philo, t_data *data);
int			ft_strcmp(char *s1, char *s2);
void		*timer(void *data_philo);
void		*life(void *philos);
void		print_philo(char *str, t_philo *philo);
void		philo_take_forks(t_philo *philo);
int			philo_fork(t_philo *philo, long int last_meal);
int			philo_eat(t_philo *philo, long int last_meal);
int			finish_eating(t_philo *philo);
int			philo_sleep(t_philo *philo, long int last_meal);
int			check_struct(t_data *data);

#endif
