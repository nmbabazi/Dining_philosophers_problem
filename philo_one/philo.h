/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:00:51 by user42            #+#    #+#             */
/*   Updated: 2021/01/24 13:34:50 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>

int					g_died;

typedef	struct		s_data
{
	int				nb_philo;
	long			timer_start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meal;
	int				isfull;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	end;
}					t_data;

typedef	struct		s_philosopher
{
	int			meals;
	long		t_start;
	long		t_now;
	int			id;
	pthread_t	thread;
	t_data		*data;
	int			right;
	int			left;
}					t_philosopher;

int					pars_arg(int ac, char **av);
void				ft_clear(t_philosopher *philosopher, t_data *data);

int					init_data(t_data *data, char **av);
void				init_philosopher(t_philosopher *philosopher, t_data *data);
int					start_threads(t_philosopher *philosopher, t_data *data);
int					creat_thread(t_philosopher *philosopher, t_data *data);

void				*routine(void *philosopher);
void				*liveness_check(void *philosopher);
void				philo_sleep(t_philosopher *philo, t_data *data);
int					philo_eat(t_philosopher *philo, t_data *data);

int					print_state(t_philosopher *philo, t_data *data,
								const char *str);
int					print_death(t_philosopher *philo, t_data *data,
								const char *str);
void				nbr_copy(char dest[100], long nb, int index, int nb_len);
void				str_copy(char dest[100], const char *str, int index);
int					len_nb(unsigned int nb);

int					print_error(char *str);
void				ft_sleep(long d);
long				gettime(void);

int					ft_atoi(const char *nb);
int					ft_isdigit(int c);
int					str_isdigit(char *str);
size_t				ft_strlen(char const *str);
void				*ft_calloc(size_t len);

#endif
