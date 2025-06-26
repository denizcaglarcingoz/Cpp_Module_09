EXECUTABLE := PmergeMe
INCLUDES = PmergeMe.hpp
CPP = c++
OBJ_DIR = obj
SRCS = main.cpp PmergeMe.cpp

OBJ = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
# (VAR : PATTERN = REPLACEMENT) Take the each word in VAR matching the PATTERN and turn into REPLACEMENT


CFLAGS = -Wall -Wextra -Werror -I. -std=c++98

RM := rm -f

all: $(EXECUTABLE)
#target: prerequisites… "if executable up to date "

$(EXECUTABLE): $(OBJ)
	$(CPP) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)


$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CPP) $(CFLAGS)  -c $< -o $@
clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re