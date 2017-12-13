OPTIONS = -O2 -Wall -ffast-math
EXEC = test

all: executable
executable:
	gcc $(OPTIONS) -o $(EXEC) src/main.c -lm -llapack -lblas 

