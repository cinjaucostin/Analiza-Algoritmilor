CC = gcc -g
FLAGS = -o

build: test1 test2

run-p1: 
	./test1

run-p2: 
	./test2

run-best:
	./test1

test1: test1.c utils.c miller_rabin.c
	$(CC) test1.c utils.c miller_rabin.c $(FLAGS) test1

test2: test2.c utils.c fermat.c
	$(CC) test2.c utils.c fermat.c $(FLAGS) test2

.PHONY: clean

clean:
	rm -rf *.o test1 test2 out/*.out performances/*