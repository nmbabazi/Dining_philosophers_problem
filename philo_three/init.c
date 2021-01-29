/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:42:49 by user42            #+#    #+#             */
/*   Updated: 2021/01/23 15:52:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*wait_meals(void *data)
{
	t_data	*dt;
	int		philo_full;

	dt = (t_data *)data;
	philo_full = 0;
	while (!g_died)
	{
		sem_wait(dt->meals);
		philo_full++;
		if (philo_full > dt->nb_philo)
		{
			write(1, "Everyone is full", 17);
			kill(0, SIGINT);
		}
	}
	return (NULL);
}

void	meal_check(t_data *data)
{
	pthread_t	full;

	pthread_create(&full, NULL, wait_meals, data);
	pthread_detach(full);
	return ;
}

int		creat_process(t_philosopher *philosopher, t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	pid = 1;
	while (i < data->nb_philo && pid > 0)
	{
		if ((pid = fork()) < 0)
			return (print_error("error on fork"));
		else if (!pid)
			status = routine(&philosopher[i]);
		i++;
	}
	meal_check(data);
	if (pid > 0)
		waitpid(-1, &status, 0);
	return (0);
}

int		init_sem(t_data *data)
{
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("end");
	sem_unlink("meals");
	data->fork = sem_open("fork", O_CREAT | O_RDWR, 0660, (data->nb_philo / 2));
	data->write = sem_open("write", O_CREAT | O_RDWR, 0660, 1);
	data->end = sem_open("end", O_CREAT | O_RDWR, 0660, 1);
	data->meals = sem_open("meals", O_CREAT | O_RDWR, 0660, 1);
	return (1);
}

int		init_data(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->isfull = data->nb_philo;
	if (av[5])
		data->nb_meal = ft_atoi(av[5]);
	else
		data->nb_meal = -1;
	if (!init_sem(data))
		return (-1);
	return (1);
}
