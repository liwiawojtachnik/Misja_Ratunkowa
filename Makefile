CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -lm
# -lm jest konieczne do linkowania biblioteki matematycznej (math.h)

# Pliki wynikowy
TARGET = pso

# Lista plików źródłowych i obiektowych
SRCS = main.c map.c pso.c logger.c utils.c
OBJS = $(SRCS:.c=.o)

# Domyślny cel
all: $(TARGET)

# Linkowanie
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Kompilacja plików .c na .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Czyszczenie projektu (usuwanie plików tymczasowych)
clean:
	rm -f $(OBJS) $(TARGET) *.csv

.PHONY: all clean