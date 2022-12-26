all: clean build run

clean:
	rm -rf ./array.sh

build:
	gcc ./array.c -o ./array.sh -lm

run:
	./array.sh


