.PHONY: all

all: clean build run

build:
	g++ -Wall main.c utils.c

clean:
	rm -f a.out

run:
	./a.out
