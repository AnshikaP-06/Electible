# Electible Makefile
# SE 2XC3 Lab 7.2 - Team Assignment
# Team 33

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
LIBS = -lm

# Source files
SOURCES = main.c data.c filter.c sort.c sort_code.c sort_difficulty.c sort_rating.c sort_title.c sort_workload.c sort_multi.c ui.c

# Build the program
all:
	$(CC) $(CFLAGS) -o main $(SOURCES) $(LIBS)

# Run the program
run: all
	./main

# Run with test input
test: all
	printf "3\n1\n1\n7\n7\n" | ./main


# Clean up compiled files
clean:
	rm -f main

# Rebuild everything
rebuild: clean all
