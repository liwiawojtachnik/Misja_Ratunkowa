CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -lm

TARGET = pso

SRCS = main.c map.c pso.c logger.c utils.c tests.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.csv

.PHONY: all clean