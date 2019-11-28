# defining makefile varriables:
CC=g++
CFLAGS=-c
headers=game.h player.h weapon.h position.h sponsor.h header.h
objects=main.o game.o player.o weapon.o position.o sponsor.o functions.o

#defining rules:
all: out

out: $(objects) $(headers)
	$(CC) $(objects) -o out

main.o: main.cpp $(headers)
	$(CC) $(CFLAGS) main.cpp

game.o: game.cpp $(headers)
	$(CC) $(CFLAGS) game.cpp

player.o: player.cpp player.h weapon.h position.h weapon.h
	$(CC) $(CFLAGS) player.cpp

weapon.o: weapon.cpp weapon.h
	$(CC) $(CFLAGS) weapon.cpp

position.o: position.cpp position.h
	$(CC) $(CFLAGS) position.cpp

sponsor.o: sponsor.cpp sponsor.h
	$(CC) $(CFLAGS) sponsor.cpp

functions.o: functions.cpp header.h game.h
	$(CC) $(CFLAGS) functions.cpp

clean:
	rm -rf *o out