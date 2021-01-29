NAME = philo_three

CFLAGS  = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS = 	main.c \
		utiles.c \
		routine.c \
		print.c \
		init.c \
		lib.c \

OBJSRCS = $(SRCS:.c=.o) 

$(NAME) : $(OBJSRCS)
	@echo "[Remove last version...]"
	@rm -rf philo_three
	@gcc $(CFLAGS) -I philo.h -o $(NAME) $(OBJSRCS) -lpthread
	@echo "[Done !]"

all : $(NAME)

clean :
	rm -rf $(OBJSRCS)

fclean : clean
	rm -rf $(NAME)

re : fclean all