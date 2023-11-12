compiler = gcc
objects = dknow.o error.o
flags = -Wall -Wextra -Wpedantic

dknow: $(objects)
	$(compiler) -o dknow $(objects)

%.o: %.c
	$(compiler) -c $(flags) $^

clear:
	rm -f $(objects) dknow
	clear
