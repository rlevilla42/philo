/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:03:56 by rlevilla          #+#    #+#             */
/*   Updated: 2023/11/27 22:31:26 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_state(t_env *env, long int start_time, int id, char *state)
{
	long int	diff_time;
	long int	time;

	time = get_time();
	diff_time = time - start_time;
	pthread_mutex_lock(env->printf_state);
	if (dead_loop(env) == 1)
	{
		pthread_mutex_unlock(env->printf_state);
		return ;
	}
	else
		printf("%ld ms %d %s\n", diff_time, id, state);
	pthread_mutex_unlock(env->printf_state);
	return ;
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (argc < 5 || argc > 6)
		return (-1);
	while (j < argc)
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < 48 || argv[j][i] > 57)
				return (-1);
				i++;
		}
		j++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	fork[MAX_PHILO];
	t_philo			ph[MAX_PHILO];
	t_env			env;

	if (check_args(argc, argv) == -1)
	{
		write(2, "error arguments\n", 18);
		return (-1);
	}
	if (init_all(&env, ph, fork, argv) == -1)
	{
		destroy_all("error in init_all function", &env, fork);
		return (-1);
	}
	destroy_all(NULL, &env, fork);
	return (0);
}
