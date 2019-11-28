# defining variables:
CC=g++
CFLAGS=-c
headers=row.h matrix.h
objects=main.o row.o matrix.o

#defining rules:
all: out

out: $(objects) $(headers)
	$(CC) $(objects) -o out

main.o: main.cpp $(headers)
	$(CC) $(CFLAGS) main.cpp

row.o: row.cpp $(headers)
	$(CC) $(CFLAGS) row.cpp

matrix.o: matrix.cpp $(headers)
	$(CC) $(CFLAGS) matrix.cpp

clean:
	rm -rf *o out	