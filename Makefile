PROGNAME = tree_of_expression
CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror -Wextra -pedantic -w -pipe -O3 -fno-stack-protector

all: program.c structs parser.c stack.c tree.c clean
	$(CC) $(CFLAGS) program.c -L. -l$(PROGNAME) -Wl,-rpath,. -o $(PROGNAME)
structs: parser.h parser.c stack.h stack.c tree.h tree.c
	$(CC) $(CFLAGS) -c -fPIC stack.c
	$(CC) $(CFLAGS) -c -fPIC parser.c
	$(CC) $(CFLAGS) -c -fPIC tree.c
	$(CC) $(CFLAGS) -shared -o lib$(PROGNAME).so -Wl,-soname,lib$(PROGNAME).so stack.o parser.o tree.o
clean:
	rm -f *.o