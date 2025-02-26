NAME			=	philo

SRC				=	script/main.c\
					script/utils/ft_alist.c\
					script/utils/ft_atol.c\
					script/utils/ft_calloc.c\
					script/utils/ft_lstadd_back.c\
					script/utils/ft_lstadd_front.c\
					script/utils/ft_lstclear.c\
					script/utils/ft_lstdelone.c\
					script/utils/ft_lstlast.c\
					script/utils/ft_lstnew.c\
					script/utils/ft_lst_rotate.c\
					script/utils/ft_lstsize.c\
					script/utils/ft_lst_swap.c\

CFLAGS			=	-Wall -Werror -Wextra -pthread -Ofast

all:	$(NAME) info

hello:
	@echo "\e[48;2;100;0;100;1m Welcome to Philo Makefile !\e[0m\n"

info: hello
	@echo "\e[48;2;70;70;70;1m Philo usage : \e[0m\n"
	@echo "./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"

$(NAME): ${SRC}
	@echo "\e[48;2;0;155;0;1m Compile Philo \e[0m\n"
	cc ${SRC} ${CFLAGS} -o $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

fclean: hello clean
	@echo "\e[48;2;155;100;0;1m Uninstall Philo \e[0m\n"
	$(RM) $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

re:	fclean all

.PHONY: all clean fclean re
