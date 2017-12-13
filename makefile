OPTIONS = -O2 -Wall 
EXEC = test

all: executable
executable:
	gcc $(OPTIONS) -o $(EXEC) src/main.c -lm -llapack -lblas 

