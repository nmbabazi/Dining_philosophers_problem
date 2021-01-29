/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:38:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 13:29:50 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	long			ret;
	struct timeval	t1;

	ret = 0;
	gettimeofday(&t1, NULL);
	ret = t1.tv_sec * 1000;
	ret += t1.tv_usec / 1000;
	return (ret);
}

void	ft_sleep(long d)
{
	struct timeval	tmp;
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&tmp, NULL);
		if ((((long)(tmp.tv_sec - start.tv_sec)) * 1000000 +
		((long)(tmp.tv_usec - start.tv_usec))) >= d)
			return ;
	}
}

int		print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

size_t	ft_strlen(char const *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
