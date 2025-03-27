NAME			=	philo
D_NAME			=	d_philo
T_NAME			=	d_philo_tsan
A_NAME			=	d_philo_asan

SRC				=	script/main.c\
					script/philo.c\
					script/utils/ft_alist.c\
					script/utils/ft_atol.c\
					script/utils/ft_calloc.c\
					script/utils/ft_lstadd_back.c\
					script/utils/ft_lstadd_front.c\
					script/utils/ft_lstclear.c\
					script/utils/ft_lstdelone.c\
					script/utils/ft_lstnew.c\
					script/utils/philo_write.c\
					script/utils/philo_other.c\
					script/utils/philo_lstiter.c\

CFLAGS			=	-Wall -Werror -Wextra -pthread
DATA_RACE_FLAGS	=	-Wall -Werror -Wextra -pthread -fsanitize=thread
ADDRESS_FLAGS	=	-Wall -Werror -Wextra -pthread -fsanitize=address

all:	$(NAME)	info

debug: d_info ${SRC}
	@echo "\e[48;2;0;155;0;1m Compile debug Philo \e[0m\n"
	gcc ${SRC} ${DATA_RACE_FLAGS} -o $(T_NAME)
	gcc ${SRC} ${ADDRESS_FLAGS} -o $(A_NAME)
	gcc ${SRC} -D PHILO_DEBUG=1 ${CFLAGS} -o $(D_NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

hello:
	@echo "\e[48;2;100;0;100;1m	Welcome	to Philo Makefile !\e[0m\n"

info: hello
	@echo "\e[48;2;70;70;70;1m Philo usage : \e[0m\n"
	@echo "./philo <number_of_philosophers>	<time_to_die> <time_to_eat>	<time_to_sleep>	[number_of_times_each_philosopher_must_eat]\n"

d_info:	hello
	@echo "\e[48;2;70;70;70;1m Philo usage : \e[0m\n"
	@echo "./d_philo <number_of_philosophers> <time_to_die>	<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"

$(NAME): ${SRC}
	@echo "\e[48;2;0;155;0;1m Compile Philo	\e[0m\n"
	gcc ${SRC} ${CFLAGS}	-o $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

fclean:	hello clean
	@echo "\e[48;2;155;100;0;1m	Uninstall Philo	\e[0m\n"
	$(RM) $(NAME) $(D_NAME)	$(T_NAME) $(A_NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

re:	fclean all

.PHONY:	all	clean fclean re