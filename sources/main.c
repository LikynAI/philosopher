/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:33:35 by alex              #+#    #+#             */
/*   Updated: 2022/07/05 11:56:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	static long long	starttime = 0;
	struct timeval		tv;
	long long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	if (starttime == 0)
		starttime = milliseconds;
	return (milliseconds - starttime);
}

static int	stop_simulation(t_input *i, int died, pthread_mutex_t	*mutexes)
{
	i->n_of_philo = 0;
	pthread_mutex_lock(&(mutexes[0]));
	if (died)
		printf("%d %d died\n", get_time(), died);
	else
		printf("%d Vse naelis\'\n", get_time());
	pthread_mutex_unlock(&(mutexes[0]));
	usleep(i->time_to_eat + i->time_to_sleep);
	exit(0);
}

static void	simulation(t_input *i, t_philo *p, pthread_mutex_t	*mutexes)
{
	int	b;
	int	j;

	while (1)
	{	
		b = 1;
		j = -1;
		while (++j < i->n_of_philo)
		{
			if (is_dead(p[j]))
				stop_simulation(i, j + 1, mutexes);
			if (i->number_of_times_each_t_philosopher_must_eat < 0
				|| p[j].eat_times
				< i->number_of_times_each_t_philosopher_must_eat)
				b = 0;
		}
		if (b)
			stop_simulation(i, 0, mutexes);
	}
	free(p);
	clear_data(mutexes, i->n_of_philo);
}

static void	start_simulation(t_input *i)
{
	int				j;	
	t_philo			*p;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;

	threads = malloc(sizeof(pthread_t) * i->n_of_philo);
	mutexes = malloc(sizeof(pthread_mutex_t) * (i->n_of_philo + 1));
	p = malloc(sizeof(t_philo) * i->n_of_philo);
	philo_init(&p, i, mutexes);
	j = 0;
	while (j < i->n_of_philo)
	{
		usleep(10);
		pthread_create(&threads[j], NULL, &manager, &(p[j]));
		j += 2;
	}
	j = 1;
	while (j < i->n_of_philo)
	{
		usleep(10);
		pthread_create(&threads[j], NULL, &manager, &(p[j]));
		j += 2;
	}
	simulation(i, p, mutexes);
	free(threads);
}

int	main(int argc, char *argv[])
{
	t_input	i;

	if (argc == 6 || argc == 5)
	{
		i.n_of_philo = ft_atoi(argv[1]);
		i.time_to_die = ft_atoi(argv[2]);
		i.time_to_eat = ft_atoi(argv[3]);
		i.time_to_sleep = ft_atoi(argv[4]);
		i.number_of_times_each_t_philosopher_must_eat = -1;
	}
	else
		return (0);
	if (argc == 6)
		i.number_of_times_each_t_philosopher_must_eat = ft_atoi(argv[5]);
	start_simulation(&i);
}
