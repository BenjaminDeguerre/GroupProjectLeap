#include "Communicator.hpp"
#include <iostream>

Communicator::Communicator() {
  WSAStartup(MAKEWORD(2,2), &WSAData);
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sin.sin_addr.s_addr = inet_addr("192.168.0.20");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(2100);
  iResult = connect(sock, (SOCKADDR *)&sin, sizeof(sin));

  if (iResult == SOCKET_ERROR) {
    wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
    iResult = closesocket(sock);
    if (iResult == SOCKET_ERROR)
      wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
    WSACleanup();
  }
  std::cout << "Connected to server" << '\n';
}

Communicator::~Communicator(){
  closesocket(sock);
  WSACleanup();
}

int Communicator::sendData(char *data) {
  std::cout << data << '\n';
  return send(sock, data, 100, 0);
}
