/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:34:58 by rlevilla          #+#    #+#             */
/*   Updated: 2023/11/27 22:31:31 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_env(t_env *env, t_philo *ph, char **argv)
{
	env->philo_nb = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] == NULL)
	{
		env->nb_meals_needed = -1;
		env->meals_flag = -1;
	}
	else if (ft_atoi(argv[5]) == 0)
		return (-1);
	else if (argv[5])
	{
		env->nb_meals_needed = ft_atoi(argv[5]);
		env->meals_flag = 0;
	}
	env->start_time = get_time();
	env->dead_flag = 0;
	env->ph = ph;
	return (0);
}

int	init_fork(t_env *env, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < env->philo_nb)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (-1);
	}
	env->printf_state = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(env->printf_state, NULL);
	env->last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(env->last_meal, NULL);
	env->dead_loop = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(env->dead_loop, NULL);
	env->meals_nb = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(env->meals_nb, NULL);
	return (0);
}

int	init_philo(t_env *env, t_philo *ph, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < env->philo_nb)
	{
		ph[i].ph_id = i + 1;
		ph[i].nb_meals_needed = env->nb_meals_needed;
		if (env->nb_meals_needed > 0)
			ph[i].meals_eaten = 0;
		else
			ph[i].meals_eaten = -1;
		ph[i].l_fork = &fork[i];
		if (ph[i].ph_id == 1)
			ph[i].r_fork = &fork[env->philo_nb - 1];
		else
			ph[i].r_fork = &fork[i - 1];
		if (env->nb_meals_needed > 0)
			ph[i].nb_meals_needed = env->nb_meals_needed;
		else
			ph[i].nb_meals_needed = -1;
		ph[i].start_time = env->start_time;
		ph[i].last_meal = 0;
		ph[i].env = env;
	}
	return (0);
}

int	init_threads(t_env *env, t_philo *ph, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	if (env->philo_nb == 1)
	{
		printf_state(env, env->start_time, 1, "has taken a fork");
		ft_usleep(env->time_to_die);
		printf_state(env, env->start_time, 1, "died");
		return (0);
	}
	while (++i < env->philo_nb)
	{
		if (pthread_create(&ph[i].th, NULL, &routine, &ph[i]) != 0)
			destroy_all("error in pthread_join", env, fork);
	}
	check_death(env);
	i = -1;
	while (++i < ph[0].philo_nb)
	{
		if (pthread_join(ph[i].th, NULL) != 0)
			destroy_all("error in pthread_join", env, fork);
		ft_usleep(1);
	}
	return (0);
}

int	init_all(t_env *env, t_philo *ph, pthread_mutex_t *fork, char **argv)
{
	if (init_env(env, ph, argv) == -1)
		return (error_state("error in init_env", env, fork));
	if (init_fork(env, fork) != 0)
		return (error_state("error in init_fork", env, fork));
	if (init_philo(env, ph, fork) != 0)
		return (error_state("error in init_philo", env, fork));
	if (init_threads(env, ph, fork) != 0)
		return (error_state("error in init_threads", env, fork));
	return (0);
}
