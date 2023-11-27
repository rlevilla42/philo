/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:11:24 by rlevilla          #+#    #+#             */
/*   Updated: 2023/11/27 22:10:47 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_env *env)
{
	pthread_mutex_lock(env->dead_loop);
	if (env->dead_flag == 1)
	{
		pthread_mutex_unlock(env->dead_loop);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(env->dead_loop);
		return (0);
	}
}

void	eat(t_philo *ph)
{
	pthread_mutex_lock(ph->l_fork);
	printf_state(ph->env, ph->start_time, ph->ph_id, "has taken a fork");
	pthread_mutex_lock(ph->r_fork);
	printf_state(ph->env, ph->start_time, ph->ph_id, "has taken a fork");
	printf_state(ph->env, ph->start_time, ph->ph_id, "is eating");
	pthread_mutex_lock(ph->env->last_meal);
	ph->last_meal = get_time();
	pthread_mutex_unlock(ph->env->last_meal);
	pthread_mutex_lock(ph->env->meals_nb);
	ph->meals_eaten++;
	pthread_mutex_unlock(ph->env->meals_nb);
	ft_usleep(ph->env->time_to_eat);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

void	sleep_think(t_philo *ph)
{
	printf_state(ph->env, ph->start_time, ph->ph_id, "is sleeping");
	ft_usleep(ph->env->time_to_sleep);
	printf_state(ph->env, ph->env->start_time, ph->ph_id, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->env->philo_nb == 1)
	{
		ft_usleep(ph->env->time_to_die);
		return (NULL);
	}
	if (ph->ph_id % 2 == 0)
		ft_usleep(ph->env->time_to_eat / 10);
	while (dead_loop(ph->env) == 0)
	{
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}
