all: src/main.c
	gcc src/*.c -o main -Wall -Wextra
	./main
