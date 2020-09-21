C_FILES := ${wildcard *.c}

.PHONY: all

all: clean build run

build: ${C_FILES}
	gcc -Wall ${C_FILES}

clean:
	rm -f a.out

run:
	./a.out
