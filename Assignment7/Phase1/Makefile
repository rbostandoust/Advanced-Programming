# defining makefile varriables
CC = g++
CFLAGS = -c
Objects = main.o my_server.o user_interface.o repository.o user.o admin.o book.o utility.o chapter.o version.o command.o editor.o
Headers = my_server.h user_interface.h repository.h user.h admin.h book.h utility.h chapter.h version.h command.h editor.h

# defining makefile rules
all: out

out: $(Objects)
	$(CC) $(Objects) -o out

main.o: main.cpp my_server.h user_interface.h
	$(CC) $(CFLAGS) main.cpp
 
my_server.o: my_server.cpp my_server.h repository.h book.h user.h admin.h utility.h exeption.h 
	$(CC) $(CFLAGS) my_server.cpp

user_interface.o: user_interface.cpp user_interface.h user.h book.h utility.h exeption.h editor.h
	$(CC) $(CFLAGS) user_interface.cpp

repository.o: repository.cpp user.h book.h my_server.h exeption.h
	$(CC) $(CFLAGS) repository.cpp

user.o: user.cpp user.h
	$(CC) $(CFLAGS) user.cpp

admin.o: admin.cpp admin.h user.h
	$(CC) $(CFLAGS) admin.cpp

book.o: book.cpp book.h user.h
	$(CC) $(CFLAGS) book.cpp

utility.o: utility.cpp utility.h
	$(CC) $(CFLAGS) utility.cpp

chapter.o: chapter.cpp chapter.h version.h utility.h command.h
	$(CC) $(CFLAGS) chapter.cpp

version.o: version.cpp version.h command.h utility.h
	$(CC) $(CFLAGS) version.cpp

command.o: command.cpp command.h chapter.h
	$(CC) $(CFLAGS) command.cpp

editor.o: editor.cpp editor.h version.h
	$(CC) $(CFLAGS) editor.cpp

clean:
	rm -rf *o out