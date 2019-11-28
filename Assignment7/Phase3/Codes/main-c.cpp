#include <cstdlib>
#include <iostream>
#include "user_interface.h"
#include "tools.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
    exit(-1);
  }
  
  UserInterface curr_user_UI("127.0.0.1", 8080);
  cout << "# connection established\n";
  
  while(true){
    curr_user_UI.handle();
  }
  
  return 0;
}
