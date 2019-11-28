#include <iostream>

//#include "user.h"
#include "my_server.h"
//#include "repository.h"
#include "user_interface.h"
// #include "admin.h"
// #include "book.h"

using namespace std;

int main(int argc, char const *argv[])
{
	MyServer server;
	UserInterface curr_user_UI(&server);
	while(true){
		curr_user_UI.handle();
	}
	return 0;
}
