OBJECTS = main.cpp client_socket.o tools.o user_interface.o editor.o chapter.o version.o command.o utility.o user.o

all: client

client: $(OBJECTS)
	g++ $(OBJECTS) -o client
	
client_socket.o: client_socket.cpp client_socket.h tools.h network_exception.h
	g++ -c client_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
	
user_interface.o: user_interface.cpp user_interface.h client_socket.h user.h utility.h
	g++ -c user_interface.cpp

editor.o: editor.cpp editor.h chapter.o
	g++ -c editor.cpp

chapter.o: chapter.cpp chapter.h version.h utility.h command.h
	g++ -c chapter.cpp

version.o: version.cpp version.h command.h utility.h
	g++ -c version.cpp

command.o: command.cpp command.h chapter.h utility.h
	g++ -c command.cpp

user.o: user.cpp user.h
	g++ -c user.cpp

utility.o: utility.cpp utility.h exeption.h
	g++ -c utility.cpp

clean:
	rm *.o client
