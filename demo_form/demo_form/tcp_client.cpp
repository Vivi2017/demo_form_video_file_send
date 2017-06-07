#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
 
#include "tcp_client.h"
#pragma comment(lib, "Ws2_32.lib")

TCP_Client::TCP_Client(char* servername)
{
	szServerName = servername;
	ConnectSocket = INVALID_SOCKET;
}

bool TCP_Client::Start() {
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	struct addrinfo	*result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(szServerName, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return false;
	}

	ptr = result;

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %d\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	// Connect to server
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);



	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return false;
	}

	return true;
};

// Free the resouces
void TCP_Client::Stop() {
	int iResult = shutdown(ConnectSocket, SD_SEND);

	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		return;
	}

	closesocket(ConnectSocket);
	ConnectSocket = INVALID_SOCKET;
	WSACleanup();
};

// Send message to server
bool TCP_Client::Send(char* szMsg)
{
	int sendL = strlen(szMsg);
	int iResult = send(ConnectSocket, szMsg, strlen(szMsg), 0);

	if (iResult == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		Stop();
		return false;
	}

	return true;
};
// Send message to server
bool TCP_Client::Send(char* szMsg, long size)
{
	int sendL = strlen(szMsg);
	int iResult = send(ConnectSocket, szMsg, size, 0);

	if (iResult == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		Stop();
		return false;
	}

	return true;
};
int TCP_Client::Recv(char *msgRecv)
{
	//char recvbuf[DEFAULT_BUFFER_LENGTH];
	memset(msgRecv, 0, DEFAULT_BUFFER_LENGTH);
	int iResult = recv(ConnectSocket, msgRecv, DEFAULT_BUFFER_LENGTH, 0);

	if (iResult > 0)
	{
		//char msg[DEFAULT_BUFFER_LENGTH];

		//	strncpy(msgRecv, recvbuf, iResult);

		printf("Received: %s\n", msgRecv);


	}


	return iResult;
};

int TCP_Client::Recv(char *msgRecv, int size)
{

	int iResult = recv(ConnectSocket, msgRecv, size, 0);

	return iResult;
};

int TCP_Client::Select()
{
	//int             i;
	fd_set         fdread;
	int             ret;
	struct timeval tv = { 1, 0 };
	
	
	FD_ZERO(&fdread);
	
	FD_SET(ConnectSocket, &fdread);
	                    // We only care read event 
	ret = select(0, &fdread, NULL, NULL, &tv);

	if (ret == WSAENETRESET)
	{
		return -1;
	}
	else if (ret > 0)
	{
		if (FD_ISSET(ConnectSocket, &fdread))
		{
			return 1;
		}
	}
	return 0;
};
SOCKET TCP_Client::getSocket() {
	return ConnectSocket;
};