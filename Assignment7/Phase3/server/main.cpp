#include <cstdlib>
#include "my_server.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "valid operation: " << argv[0] << " [port number]\n";
    exit(-1);
  }
  
  MyServer server(Tools::mystoi(argv[1]));
  server.run();
  
  return 0;
}
