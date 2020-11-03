#
# Makefile
#
# CS50 AP
# Problem 3-6
#

all: find generate

find: find.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o find.o find.c helpers.c -lcs50 -lm

generate: generate.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o generate.o generate.c

clean:
	rm -f *.o a.out core find generate