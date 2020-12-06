CC=gcc
CFLAGS=-I $(LDIR)
LDIR =lib
ODIR=bin
RM= rm -f
INC=include
FLAGS= -Wall -Werror -pedantic -Wextra -Wconversion -std=gnu11

main : main.o dataN1_read.o dataN1_header.o list.o cjson.o
	$(CC) -g $(FLAGS) $^ -o $(ODIR)/$@

main.o: main.c
	$(CC) -c $(FLAGS) $^ -o $@

dataN1_read.o: dataN1_read.c dataN1_read.h 
	$(CC) -c $(FLAGS) $< -o $@

dataN1_header.o: dataN1_header.c dataN1_header.h
	$(CC) -c $(FLAGS) $< -o $@

list.o: $(INC)/list.c $(INC)/list.h
	$(CC) -c $(FLAGS) $< -o $@

cjson.o: $(INC)/cJSON.c $(INC)/cJSON.h
	$(CC) -c $(FLAGS) $< -o $@

.PHONY: all clean

clean :
	rm -f $(ODIR)/*.o *.o *.ghc $(ODIR)/*.ghc main $(ODIR)/main
