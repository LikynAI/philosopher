/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:00:51 by alex              #+#    #+#             */
/*   Updated: 2022/07/05 11:13:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_data(pthread_mutex_t	*mutexes, int n)
{
	int	i;

	i = -1;
	while (++i < n + 1)
		pthread_mutex_destroy(&(mutexes[i]));
	free(mutexes);
}

static int	over_int_handler(int isNeg)
{
	if (isNeg == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long			i;
	int					is_neg;
	unsigned long long	ans;

	i = 0;
	is_neg = 1;
	ans = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			is_neg *= -1;
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans *= 10;
		ans += str[i++] - '0';
	}
	if ((ans > 2147483647 && is_neg == 1)
		|| (ans > (unsigned long long)(2147483647) + 1 && is_neg == -1))
		return (over_int_handler(is_neg));
	return (is_neg * (int)ans);
}
