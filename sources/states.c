/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:28:01 by alex              #+#    #+#             */
/*   Updated: 2022/07/01 17:06:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_sleep(t_philo *p)
{
	print_data("is sleep\n", p->id, p);
	usleep(p->inp->time_to_sleep * 1000);
}

void	eat(t_philo *p)
{
	print_data("is eating\n", p->id, p);
	p->lastmeal = get_time();
	usleep(p->inp->time_to_eat * 1000);
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(p->rfork);
	p->eat_times++;
	p_sleep(p);
}

int	thinking(t_philo *p)
{
	pthread_mutex_lock(p->lfork);
	print_data("has taken a fork\n", p->id, p);
	pthread_mutex_lock(p->rfork);
	print_data("has taken a fork\n", p->id, p);
	if (p->rfork != p->lfork)
		return (0);
	return (1);
}

int	is_dead(t_philo p)
{
	return (get_time() - p.lastmeal > p.inp->time_to_die);
}
