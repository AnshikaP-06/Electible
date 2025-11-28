
# Build all source files into 'main'
all:
	gcc -std=c11 -Wall -Wextra -Iinclude main.c sort_code.c sort_difficulty.c sort_rating.c sort_title.c sort_workload.c -o main

# Clean build artifacts
clean:
	rm -f main
