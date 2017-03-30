#include <winsock2.h>
#include <string>

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
  int sendData(string data);
}
