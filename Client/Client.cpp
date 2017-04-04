#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")



int main()
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[100];
    int iResult;
    std::string s;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    /* Tout est configuré pour se connecter sur IRC, haarlem, Undernet. */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(30001);
    iResult = connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    if (iResult == SOCKET_ERROR) {
      wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
      iResult = closesocket(sock);
      if (iResult == SOCKET_ERROR)
        wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
      WSACleanup();
      return 1;
    }

    while (true) {
      int r = recv(sock, buffer, sizeof(buffer), 0);
      s.append(buffer);
      std::cout << s << '\n';
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}
