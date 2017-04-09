#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

class Communicator {
private:
  WSADATA WSAData;
  SOCKET sock;
  SOCKADDR_IN sin;
  int iResult;

public:
  Communicator();
  ~Communicator();
  int sendData(std::string data, bool delay = true);
};
