SRCS				= mein.cpp

NAME				= test

OBJS				= $(SRCS:.cpp=.o)
DEPS				= $(SRCS:.cpp=.d)

CXX					= clang++
RM 					= rm -f
CXXFLAGS			= -Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address
CPPFLAGS			= -MMD -I.

FT					= -D SWITCH=1
STD					= -D SWITCH=0
SEED				= 21

BOLDMAGENTA			= \033[1m\033[35m
BOLDRED				= \033[1m\033[31m
RESET				= \033[0m\n

all:				$(NAME)

ft:
					@make fclean -s
					@printf "$(BOLDMAGENTA)Compiling FT_Containers$(RESET)"
					@make CPPFLAGS="$(CPPFLAGS) $(FT)" all
					@printf "\n"
					./$(NAME) $(SEED)
					@(time ./$(NAME) $(SEED)) &> ft.txt; echo ft >> ft.txt

std:
					@make fclean -s
					@printf "$(BOLDMAGENTA)Compiling STD_Containers$(RESET)"
					@make CPPFLAGS="$(CPPFLAGS) $(STD)" all
					@printf "\n"
					./$(NAME) $(SEED)
					@(time ./$(NAME) $(SEED)) &> std.txt; echo std >> std.txt

leaks:				ft
					leaks --atExit -- ./$(NAME)

diff:
					@printf "$(BOLDRED)Testing difference between FT and STD$(RESET)\n"
					@make ft
					@printf "\n"
					@make std
					@printf "\n"
					@printf "$(BOLDRED)========= diff =========$(RESET)"
					@diff ft.txt std.txt || true

$(OBJS):			Makefile

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

-include			$(DEPS)

clean:
					$(RM) $(OBJS) $(DEPS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

sc:
					rm -rf *.o *.a */*.o */*.a */*.d *.d $(NAME)

.PHONY:				all clean fclean re bonus \
					sc

# .SILENT:
# leaks --atExit --
