CC=gcc
FLAGS=-Wall -Wextra -Wshadow -std=gnu99 -g
LIBS=
BIN=/usr/bin/

bh: main.c
	${CC} main.c ${FLAGS} ${LIBS} -o bh

clean:
	rm bh


