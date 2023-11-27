/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:12:50 by rlevilla          #+#    #+#             */
/*   Updated: 2023/11/27 22:26:14 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	buffer;
	int	countminus;

	i = 0;
	countminus = 1;
	buffer = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			countminus = -1;
		i++;
	}
	if (str[i] < 48 || str[i] > 57)
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		buffer = (buffer * 10) + (str[i] - 48);
		i++;
	}
	return (buffer * countminus);
}

long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	sleep;

	sleep = get_time();
	while (get_time() - sleep < time)
		usleep(time / 10);
	return ;
}

void	destroy_all(char *str, t_env *env, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
			i++;
		write(2, str, i);
		write(2, "\n", 1);
	}
	i = -1;
	free(env->printf_state);
	free(env->last_meal);
	free(env->dead_loop);
	free(env->meals_nb);
	pthread_mutex_destroy(env->printf_state);
	pthread_mutex_destroy(env->last_meal);
	pthread_mutex_destroy(env->dead_loop);
	pthread_mutex_destroy(env->meals_nb);
	while (++i < env->philo_nb)
		pthread_mutex_destroy(&forks[i]);
	return ;
}

int	error_state(char *str, t_env *env, pthread_mutex_t *forks)
{
	printf("%s\n", str);
	destroy_all(str, env, forks);
	return (-1);
}
