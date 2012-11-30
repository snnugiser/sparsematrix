CC = g++
TARGET = ./main
Objects = main.o SparseMatrix.o pair.o Trituple.o
main:$(Objects)
	$(CC) -g -o main main.o SparseMatrix.o pair.o Trituple.o
main.o: main.cpp SparseMatrix.h Trituple.h pair.h
pair.o: pair.cpp pair.h
SparseMatrix.o: SparseMatrix.cpp  SparseMatrix.h Trituple.h pair.h
Trituple.o: Trituple.cpp Trituple.h
clean:
	rm *.o

