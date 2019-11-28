OBJECTS = main.cpp server_socket.o server.o tools.o my_server.o repository.o book.o chapter.o version.o command.o user.o utility.o

all: server

server: $(OBJECTS)
	g++ $(OBJECTS) -o server

server.o: server.cpp server.h
	g++ -c server.cpp
	
server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp

my_server.o: my_server.cpp my_server.h repository.h user.h exeption.h server.h
	g++ -c my_server.cpp

repository.o: repository.cpp repository.h book.h user.h utility.h exeption.h
	g++ -c repository.cpp

book.o: book.cpp book.h utility.h chapter.h user.h
	g++ -c book.cpp
	
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
	rm *.o server
