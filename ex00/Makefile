NAME = a.out btc
CODEDIRS = . 
INCDIRS = .
SOURCETYPE = cpp

CC = g++
OPT = -O0
DEPFLAGS = -MP -MD
CFLAGS=-Wall -Wextra -Werror -std=c++98 -I. $(OPT) 

CFILES = main.cpp BitcoinExchange.cpp
OBJECTS = $(patsubst %.$(SOURCETYPE),%.o,$(CFILES))
DEPFILES = $(patsubst %.$(SOURCETYPE),%.d,$(CFILES))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.$(SOURCETYPE)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c -o $@ $<


clean:
	rm -rf $(OBJECTS) $(DEPFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

-include $(DEPFILES)

.PHONY: all %.o $(NAME) clean fclean re diff