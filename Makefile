SRCS				= mein.cpp

NAME				= test

OBJS				= $(SRCS:.cpp=.o)
DEPS				= $(SRCS:.cpp=.d)

CXX					= clang++
RM 					= rm -f
CXXFLAGS			= -Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address
CPPFLAGS			= -MMD -I.

all:				$(NAME)

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
