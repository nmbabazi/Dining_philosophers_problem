/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:38:24 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 12:16:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		len_nb(unsigned int nb)
{
	int		i;

	i = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

void	nbr_copy(char dest[100], long nb, int index, int nb_len)
{
	if (!nb)
		dest[index] = '0';
	while (nb)
	{
		(dest)[index + nb_len] = nb % 10 + '0';
		nb /= 10;
		nb_len--;
	}
}

void	str_copy(char dest[100], const char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[index + i] = str[i];
		i++;
	}
}

int		print_state(t_philosopher *philo, t_data *data, const char *str)
{
	long	now;
	int		nb_len;
	int		i;
	char	msg[100];

	i = 0;
	while (i < 100)
		msg[i++] = '\0';
	pthread_mutex_lock(&data->write);
	now = gettime() - data->timer_start;
	nb_len = len_nb(now);
	nbr_copy(msg, now, 0, nb_len - 1);
	str_copy(msg, "\t", nb_len);
	nb_len += 1;
	nbr_copy(msg, philo->id + 1, nb_len - 1, len_nb(philo->id + 1));
	nb_len += len_nb(philo->id + 1);
	str_copy(msg, " ", nb_len);
	nb_len += 1;
	str_copy(msg, str, nb_len);
	if (!g_died)
		write(1, msg, ft_strlen(msg));
	pthread_mutex_unlock(&data->write);
	return (1);
}

int		print_death(t_philosopher *philo, t_data *data, const char *str)
{
	long	current_time;
	int		nb_len;
	int		i;
	char	msg[100];

	i = 0;
	while (i < 100)
		msg[i++] = '\0';
	pthread_mutex_lock(&data->write);
	current_time = gettime() - data->timer_start;
	nb_len = len_nb(current_time);
	nbr_copy(msg, current_time, 0, nb_len - 1);
	str_copy(msg, "\t", nb_len);
	nb_len += 1;
	nbr_copy(msg, philo->id + 1, nb_len - 1, len_nb(philo->id + 1));
	nb_len += len_nb(philo->id + 1);
	str_copy(msg, " ", nb_len);
	nb_len += 1;
	str_copy(msg, str, nb_len);
	write(1, msg, ft_strlen(msg));
	pthread_mutex_unlock(&data->write);
	return (1);
}
