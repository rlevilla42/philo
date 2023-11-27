/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlevilla <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:59:44 by rlevilla          #+#    #+#             */
/*   Updated: 2023/11/27 22:28:07 by rlevilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define MAX_PHILO 300

typedef struct s_env	t_env;
typedef struct s_philo	t_philo;

typedef struct s_env
{
	long int		start_time;
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_needed;
	int				dead_flag;
	int				meals_flag;
	t_philo			*ph;
	pthread_mutex_t	*printf_state;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	*dead_loop;
	pthread_mutex_t	*meals_nb;
	pthread_mutex_t	*m_flag;
}t_env;

typedef struct s_philo
{
	int				philo_nb;
	int				ph_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_needed;
	int				meals_eaten;
	int				dead_flag;
	long int		start_time;
	long int		last_meal;
	t_env			*env;
	pthread_t		th;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}t_philo;

void		printf_state(t_env *env, long int start_time, int id, char *state);
void		ft_usleep(long int time);
long int	get_time(void);
int			ft_atoi(const char *str);
int			init_all(t_env *env, t_philo *ph,
				pthread_mutex_t *fork, char **argv);
void		*routine(void *arg);
int			dead_loop(t_env *env);
void		check_death(t_env *env);
int			check_if_all_ate(t_env *env, t_philo *ph);
int			eat_loop(t_env *env);
void		destroy_all(char *str, t_env *env, pthread_mutex_t *forks);
int			error_state(char *str, t_env *env, pthread_mutex_t *forks);

#endif
