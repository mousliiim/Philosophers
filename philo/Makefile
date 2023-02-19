ART_NAME_1 = ██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗\n
ART_NAME_2 = ██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗\n
ART_NAME_3 = ██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝\n
ART_NAME_4 = ██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗\n
ART_NAME_5 = ██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║\n
ART_NAME_6 = ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n


ART_CLEAN_1	=	 ██████╗██╗     ███████╗ █████╗ ███╗   ██╗\n
ART_CLEAN_2	=	██╔════╝██║     ██╔════╝██╔══██╗████╗  ██║\n
ART_CLEAN_3	=	██║     ██║     █████╗  ███████║██╔██╗ ██║\n
ART_CLEAN_4	=	██║     ██║     ██╔══╝  ██╔══██║██║╚██╗██║\n
ART_CLEAN_5	=	╚██████╗███████╗███████╗██║  ██║██║ ╚████║\n
ART_CLEAN_6	=	 ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝\n

################################################################################
#                                   COLORS                                     #
################################################################################

CC_GREEN				=	\e[38;5;46;1m
CC_RED					=	\e[31;1m
CC_GRAY					=	\e[38;5;15;1m

BLUE1					=	\e[38;2;0;251;255m
BLUE2					=	\e[38;2;5;234;229m
BLUE3					=	\e[38;2;11;212;202m
BLUE4					=	\e[38;2;16;194;180m
BLUE5					=	\e[38;2;23;167;149m
BLUE6					=	\e[38;2;31;136;113m

GREEN1					=	\e[38;5;154m
GREEN2					=	\e[38;5;118m
GREEN3					=	\e[38;5;82m
GREEN4					=	\e[38;5;46m
GREEN5					=	\e[38;2;0;235;0m
GREEN6					=	\e[38;5;22m

RED1					=	\e[38;5;196m
RED2					=	\e[38;5;160m
RED3					=	\e[38;5;124m
RED4					=	\e[38;5;88m
RED5					=	\e[38;2;110;0;0m
RED6					=	\e[38;5;52m

RESET					=	\e[0m

################################################################################
#                                  FUNCTIONS                                   #
################################################################################

I				=	1

NB_FILES		=	$(words $(SRCS))

PROGRESS_BAR	=	ProgressBar() {										\
					name=$$3;											\
					if [ "./$$name" = $(lastword $(SRCS)) ];			\
					then												\
						name="[DONE]";									\
					fi;													\
					progress=$$(echo "$$1*100/$(NB_FILES)*100/100" | bc);	\
					done=$$(echo "$$progress*4/10" | bc);				\
					left=$$(echo "40-$$done" | bc);						\
					fill=$$(printf "%*s" $$done | tr ' ' '\#');			\
					empty=$$(printf "%*s" $$left | tr ' ' '-');			\
					printf "\r$(CC_GRAY)Compiling source files	: ";	\
					printf "[$(CC_GREEN)$$fill$(CC_RED)$$empty$(RESET)$(CC_GRAY)] $$progress%%";\
					printf "$(CC_GREEN) %-46s$(RESET)" $$name;				\
}

PRINT_NAME		=	 printf "\n $(BLUE1)$(ART_NAME_1)$(RESET)	\
								$(BLUE2)$(ART_NAME_2)$(RESET)	\
								$(BLUE3)$(ART_NAME_3)$(RESET)	\
								$(BLUE4)$(ART_NAME_4)$(RESET)	\
								$(BLUE5)$(ART_NAME_5)$(RESET)	\
								$(BLUE6)$(ART_NAME_6)$(RESET)\n"

PRINT_CLEAN		=	printf "\n  $(RED1)$(ART_CLEAN_1)$(RESET)	\
								$(RED2)$(ART_CLEAN_2)$(RESET)	\
								$(RED3)$(ART_CLEAN_3)$(RESET)	\
								$(RED4)$(ART_CLEAN_4)$(RESET)	\
								$(RED5)$(ART_CLEAN_5)$(RESET)	\
								\40$(RED6)$(ART_CLEAN_6)$(RESET)\n"

################################################################################
#                                    MAIN                                      #
################################################################################

NAME		 		=	philo

CC			 		=	cc

CFLAGS 		 		=	-Wall -Wextra -Werror -g3 -pthread

INCLUDES	 		=	includes

################################################################################
#                           MANDATORY SOURCE FILES                             #
################################################################################

SRCS_DIR			=	./src/

SRC_FILES			=	main.c utils.c

SRCS				= 	$(addprefix $(SRCS_DIR), $(SRC_FILES))

################################################################################
#                                OBJECT FILES                                  #
################################################################################

OBJS 			 	=	$(SRCS:.c=.o)

################################################################################
#                                    RULES                                     #
################################################################################

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -I./$(INCLUDES) $^ -o $(NAME)
	@printf "\n$(CC_GRAY)Creating binary		:$(CC_GREEN) %-42s\n$(RESET)" $(NAME)
	@$(PRINT_NAME)

%.o : %.c
	@$(CC) -o $@ $(CFLAGS) -c $< -I./$(INCLUDES) -I./$(INCLUDES_BONUS)
	$(if $(findstring $<, $(firstword $(SRCS_BONUS))), $(eval NB_FILES = $(NB_FILES_BONUS)))
	@$(PROGRESS_BAR); ProgressBar $(I) $(NB_FILES) $<
	@$(eval I = $(shell echo $$(($(I) + 1))))


clean :
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@printf "$(CC_GRAY)Deleting object files	:$(CC_RED) \e[31;9m*.o\n$(RESET)"

bclean :
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@printf "$(CC_GRAY)Deleting binary files	:$(CC_RED) \e[31;9m$(NAME)\n$(RESET)"

fclean : bclean clean
	@$(PRINT_CLEAN)

re : fclean all

.PHONY : all clean bclean fclean re