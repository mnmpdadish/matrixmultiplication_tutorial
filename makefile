OPTIONS = -O2 -Wall 
EXEC = test

LIBS = -llapack -lblas
#LIBS = -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_rt -lpthread -ldl
#LIBS = -L${MKLROOT}/lib/intel64 -lmkl_rt -lpthread -ldl

all: executable
executable:
	gcc $(OPTIONS) -o $(EXEC) src/main.c -lm $(LIBS)

