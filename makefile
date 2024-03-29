CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -L/usr/local/lib -lsymengine -lgmp

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)