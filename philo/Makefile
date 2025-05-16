NAME			=	philo
D_NAME			=	d_philo
T_NAME			=	d_philo_tsan
A_NAME			=	d_philo_asan

SRC				=	ft_alist.c\
					ft_atol.c\
					ft_calloc.c\
					ft_freetab.c\
					ft_lstadd_back_bonus.c\
					ft_lstclear_bonus.c\
					ft_lstdelone_bonus.c\
					ft_lstnew_bonus.c\
					ft_putendl_fd.c\
					main.c\
					monitor.c\
					philo.c\
					time.c\
					tools.c\

CFLAGS			=	-Wall -Werror -Wextra -pthread -g
DATA_RACE_FLAGS	=	-Wall -Werror -Wextra -pthread -g -fsanitize=thread
ADDRESS_FLAGS	=	-Wall -Werror -Wextra -pthread -g -fsanitize=address

OBJ		= 	${SRC:.c=.o}

all:	$(NAME)	info

debug: d_info ${OBJ}
	@echo "\e[48;2;0;155;0;1m Compile debug Philo \e[0m\n"
	cc ${SRC} ${DATA_RACE_FLAGS} -D PHILO_BETTER=1  -o $(T_NAME)
	cc ${SRC} ${ADDRESS_FLAGS} -D PHILO_BETTER=1 -o $(A_NAME)
	cc ${SRC} -D PHILO_DEBUG=1 -D PHILO_BETTER=1 ${CFLAGS} -o $(D_NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

hello:
	@echo "\e[48;2;100;0;100;1m Welcome to Philo Makefile !\e[0m\n"

info: hello
	@echo "\e[48;2;70;70;70;1m Philo usage : \e[0m\n"
	@echo "./philo <number_of_philosophers>	<time_to_die> <time_to_eat>	<time_to_sleep>	[number_of_times_each_philosopher_must_eat]\n"

d_info:	hello
	@echo "\e[48;2;70;70;70;1m Philo usage : \e[0m\n"
	@echo "./d_philo <number_of_philosophers> <time_to_die>	<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"

$(NAME): ${OBJ}
	@echo "\e[48;2;0;155;0;1m Compile Philo	\e[0m\n"
	cc ${OBJ} ${CFLAGS}	-o $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

better: ${OBJ}
	@echo "\e[48;2;0;155;0;1m Update Philo to better print \e[0m\n"
	cc ${SRC} -D PHILO_BETTER=1  ${CFLAGS}	-o $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

clean:	hello
	@echo "\e[48;2;155;100;0;1m	Uninstall Philo dependencies	\e[0m\n"
	$(RM) $(OBJ)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

fclean:	hello clean
	@echo "\e[48;2;155;100;0;1m	Uninstall Philo	\e[0m\n"
	$(RM) $(NAME) $(D_NAME) $(T_NAME) $(A_NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

%.o: %.c
	cc ${CFLAGS} -c $< -o $@

re:	fclean all

.PHONY:	all	clean fclean re
