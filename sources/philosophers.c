/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philosophers.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: alex <alex@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/01 11:33:32 by alex			  #+#	#+#			 */
/*   Updated: 2022/07/01 15:15:53 by alex			 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

void	philo_init(t_philo **p, t_input *i)
{
	int	j;

	pthread_mutex_init(&(g_mutexes[0]), NULL);
	j = -1;
	while (++j < i->number_of_t_philosophers)
	{
		(*p)[j].eat_times = 0;
		pthread_mutex_init(&(g_mutexes[j]), NULL);
		(*p)[j].rfork = &(g_mutexes[j + 1]);
		if (j < i->number_of_t_philosophers - 1)
			(*p)[j].lfork = &(g_mutexes[j + 2]);
		else
			(*p)[j].lfork = &(g_mutexes[1]);
		(*p)[j].inp = i;
		(*p)[j].id = j + 1;
	}
}

static void	check_exit(t_philo *p)
{
	if (p->inp->number_of_t_philosophers == 0)
	{
		pthread_mutex_unlock(&(g_mutexes[0]));
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(p->rfork);
		while (1)
			usleep(100);
	}
}

void	print_data(char *text, int p_name, t_philo *p)
{
	pthread_mutex_lock(&(g_mutexes[0]));
	check_exit(p);
	printf("%d %d %s", get_time(), p_name, text);
	pthread_mutex_unlock(&(g_mutexes[0]));
}

void	*manager(void *p_void)
{
	t_philo	*p;

	p = (t_philo *)p_void;
	p->lastmeal = get_time();
	while (1)
	{
		print_data("is thinking\n", p->id, p);
		while (thinking(p))
			continue ;
		eat(p);
	}
	return (NULL);
}
