NAME			=	philo

SRCS			=	src/main.c src/utils.c

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
PURPLE= \033[38;2;255;105;180m

OBJS			=	${SRCS:.c=.o}

CFLAGS			=	-Wall -Werror -Wextra -g3 -pthread

all				:	${NAME}

.c.o	:
		@cc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME) : $(OBJS)
	@echo "\t\t\t${GREEN}========================${DEF_COLOR}"
	@echo "\t\t\t${GREEN}=== MAKE ${PURPLE}MANDATORY ⌛${DEF_COLOR}${GREEN}===${DEF_COLOR}"
	@echo "\t\t\t${GREEN}========================${DEF_COLOR}\n"
	@echo "\t\t\t${GREEN}==============================${DEF_COLOR}"
	@echo "\t\t\t${GREEN}==== ALL IS ${PURPLE}COMPILATED${DEF_COLOR} ✅${GREEN} ====${DEF_COLOR}"
	@echo "\t\t\t${GREEN}==============================${DEF_COLOR}"
	@cc $(OBJS) -o $(NAME)


clean			:
					rm -rf ${OBJS}

fclean			:	clean
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re