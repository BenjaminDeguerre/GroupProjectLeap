#include <winsock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

class Communicator {
private:
  WSADATA WSAData;
  SOCKET sock;
  SOCKET csock;
  SOCKADDR_IN sin;
  SOCKADDR_IN csin;
  int sinsize;

public:
  Communicator();
  ~Communicator();
  int sendData(char *data);
};
