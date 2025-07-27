assembler: assembler.o macro_pass.o first_pass.o lables.o externs.o second_pass.o tools.o 
	gcc -g -ansi -Wall -pedantic assembler.o macro_pass.o first_pass.o externs.o second_pass.o tools.o lables.o -lm -o assembler

assembler.o: assembler.c prototypes.h assembler.h externals.h structs.h tools.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o

macro_pass.o: macro_pass.c prototypes.h assembler.h externals.h structs.h tools.h
	gcc -c -ansi -Wall -pedantic macro_pass.c -o macro_pass.o

first_pass.o: first_pass.c prototypes.h assembler.h externals.h structs.h tools.h
	gcc -c -ansi -Wall -pedantic first_pass.c -o first_pass.o

lables.o: lables.c prototypes.h assembler.h externals.h structs.h tools.h
	gcc -c -ansi -Wall -pedantic lables.c -o lables.o

tools.o: tools.c prototypes.h assembler.h externals.h structs.h tools.h
	gcc -c -ansi -Wall -pedantic tools.c -o tools.o

second_pass.o: second_pass.c prototypes.h assembler.h externals.h structs.h
	gcc -c -ansi -Wall -pedantic second_pass.c -o second_pass.o

externs.o: externs.c prototypes.h assembler.h externals.h structs.h
	gcc -c -ansi -Wall -pedantic externs.c -o externs.o