/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:19:54 by rlevilla          #+#    #+#             */
/*   Updated: 2023/11/27 22:31:33 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_m(t_env *env)
{
	long int	diff;
	int			nb_meals;

	diff = get_time() - env->start_time;
	nb_meals = env->nb_meals_needed;
	pthread_mutex_lock(env->printf_state);
	printf("%ld ms All philos eat at least %d times\n", diff, nb_meals);
	pthread_mutex_unlock(env->printf_state);
	return ;
}

int	philo_is_dead(t_philo *ph)
{
	int long long	time;

	time = get_time();
	pthread_mutex_lock(ph->env->last_meal);
	if ((time - ph->last_meal) > ph->env->time_to_die && ph->last_meal != 0)
	{
		pthread_mutex_unlock(ph->env->last_meal);
		return (1);
	}
	pthread_mutex_unlock(ph->env->last_meal);
	return (0);
}

int	philo_eat(t_env *env, t_philo *ph, int i)
{
	pthread_mutex_lock(env->meals_nb);
	if (ph[i].meals_eaten >= env->nb_meals_needed)
	{
		pthread_mutex_unlock(env->meals_nb);
		return (1);
	}
	pthread_mutex_unlock(env->meals_nb);
	return (0);
}
/*
void	printf_meals(t_env *env, t_philo *ph, int i)
{
	pthread_mutex_lock(env->printf_state);
	pthread_mutex_lock(env->meals_nb);
	printf("ph[%d].meals_eaten = %d\n", i, ph[i].meals_eaten);
	pthread_mutex_unlock(env->meals_nb);
	pthread_mutex_unlock(env->printf_state);
	return ;
}*/
/*
				printf_meals(env, ph, 0);
				printf_meals(env, ph, 1);
				printf_meals(env, ph, 2);
				printf_meals(env, ph, 3);
				printf_meals(env, ph, 4);
				*/

int	check_if_all_ate(t_env *env, t_philo *ph)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	while (i < env->philo_nb)
	{
		if (philo_eat(env, ph, i) == 1)
		{
			finished_eating++;
			if (finished_eating == env->philo_nb)
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	check_death(t_env *env)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (++i < env->philo_nb)
	{
		flag = check_if_all_ate(env, env->ph);
		if (philo_is_dead(&env->ph[i]) == 1
			|| (flag == 1 && env->nb_meals_needed > 0))
		{
			if (flag == 1 && env->nb_meals_needed > 0)
				printf_m(env);
			else
				printf_state(env, env->start_time, env->ph[i].ph_id, "died");
			pthread_mutex_lock(env->dead_loop);
			env->dead_flag = 1;
			pthread_mutex_unlock(env->dead_loop);
			return ;
		}
		if ((i + 1) == env->philo_nb)
			i = -1;
	}
	return ;
}
