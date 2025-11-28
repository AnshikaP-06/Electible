
all:
	gcc -std=c11 -Wall -Wextra -Iinclude sort.c sort_code.c sort_difficulty.c sort_rating.c sort_title.c sort_workload.c sort_multi.c -o main

run:
	./main

test:
	printf "3\n1\n" | ./main

clean:
	rm -f main
