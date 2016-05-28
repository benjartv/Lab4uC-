INC = -I./include
CFLAGS = -Wall -multi
CC = u++

main: ./build/automata.o ./build/autoFunc.o
	@ $(CC) -o ./bin/exp ./build/automata.o ./build/autoFunc.o $(CFLAGS)
	@ echo "The compilation has been completed successfully"

build/automata.o: ./src/automata.cc
	@ echo "src/automata.c"
	@ $(CC) -c ./src/automata.cc $(INC) -o ./build/automata.o $(CFLAGS)

build/autoFunc.o: ./src/autoFunc.cc
	@ echo "src/autoFunc.cc"
	@ $(CC) -c ./src/autoFunc.cc $(INC) -o ./build/autoFunc.o $(CFLAGS)

clean:
	@ clear
	@ echo "Cleaning folders.."
	@ rm -rf build/*
	@ rm -rf bin/*
	@ rm -rf output/*

run:
	@ clear
	@ echo "uC++ exp"
	@ ./bin/exp -i ./input/mediumdna.txt -o ./output/out.txt -h 4 -L 10 -l 10