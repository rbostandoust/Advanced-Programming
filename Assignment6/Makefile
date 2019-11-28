# defining varriables
CC = g++
CFLAGS = -c
Objects = main.o mad_house.o yard.o child.o peaceful.o angry.o coward.o
Headers = mad_house.cpp yard.h child.h peaceful.h angry.h coward.h

# defining rules
all: simulation

simulation: $(Objects) 
	$(CC) $(Objects) -o simulation

main.o: main.cpp $(Headers)
	$(CC) $(CFLAGS) main.cpp

mad_house.o: mad_house.cpp $(Headers)
	$(CC) $(CFLAGS) mad_house.cpp

yard.o: yard.cpp yard.h
	$(CC) $(CFLAGS) yard.cpp

child.o: child.cpp child.h
	$(CC) $(CFLAGS) child.cpp

peaceful.o: peaceful.cpp peaceful.h child.h
	$(CC) $(CFLAGS) peaceful.cpp

angry.o: angry.cpp angry.h child.h
	$(CC) $(CFLAGS) angry.cpp

coward.o: coward.cpp coward.h child.h
	$(CC) $(CFLAGS) coward.cpp

clean:
	rm -rf *o simulation