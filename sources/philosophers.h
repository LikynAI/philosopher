/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:33:30 by alex              #+#    #+#             */
/*   Updated: 2022/07/05 11:56:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "unistd.h"
# include "printf.h"
# include "stdlib.h"
# include "sys/time.h"
# include "pthread.h"
# include <stdio.h>

typedef struct s_t_input
{
	int	n_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_t_philosopher_must_eat;
}	t_input;

typedef struct s_t_philo
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				lastmeal;
	int				id;
	t_input			*inp;
	int				eat_times;
	pthread_mutex_t	*print_mutex;
}	t_philo;

void	*manager(void *p);
void	philo_init(t_philo **p, t_input *i, pthread_mutex_t	*mutexes);
int		get_time(void);
void	print_data(char *text, int p_name, t_philo *p);
void	p_sleep(t_philo *p);
void	eat(t_philo *p);
int		thinking(t_philo *p);
int		is_dead(t_philo p);
int		ft_atoi(const char *str);
void	clear_data(pthread_mutex_t	*mutexes, int n);

#endif