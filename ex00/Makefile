EXECUTABLE := btc
INCLUDES = BitcoinExchange.hpp
CPP = c++
OBJ_DIR = obj
SRCS = main.cpp BitcoinExchange.cpp

OBJ = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -I. -std=c++98

RM := rm -f

all: $(EXECUTABLE)

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