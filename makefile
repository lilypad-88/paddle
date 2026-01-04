flags = -Wall -Wextra -g
src = src/*.c
prg = main

all: 
	gcc $(src) -o $(prg) $(flags)
	./$(prg)
