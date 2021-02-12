#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

/**
* \class Communicator
* \brief Simple class to send data to the robot.
**/
class Communicator {
private:
  WSADATA WSAData;
  SOCKET sock;
  SOCKADDR_IN sin;
  int iResult;

public:
  Communicator();
  ~Communicator();

  /**
  * \fn Communicator::sendData(std::string data, bool delay)
  * \brief Send the data to the robot.
  * \param[in] data The command to send.
  * \param[in] delay If delay, wait for 100 seconds time before continuing.
  * \return The status of the send function.
  **/
  int sendData(std::string data, bool delay = true);
};
