/**
* \file server.cpp
* \brief TCP server function definition for windows socket
* \author Gilson Varghese <gilsonvarghese7@gmail.com>
* \date June 19 2017
*/


#include "server.h"

/*
 * Function to start server to listen to a single TCP client
 * \return {int} 
 */

int startServer() {
	WSADATA wsaData;
	int iResult;

	SOCKET serverSocket = INVALID_SOCKET;
	SOCKET clientSocket = INVALID_SOCKET;

	struct  addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvBuf[DEFAULT_BUFLEN];
	int recvBufLen = DEFAULT_BUFLEN;

	/*
		Initialize Winsock
	*/
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup Filaed with error %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	/*
		Resolve the server address and port
	*/
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	/*
		Create a socket for connecting to server
	*/
	serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (serverSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld \n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	/*
		Setup TCP Listening socket
	*/
	iResult = bind(serverSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error :%ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(serverSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("Listen Failed with error: %ld\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	/*
		Accept client connection
	*/
	clientSocket = accept(serverSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		printf("Accept failed with error: %ld\n", WSAGetLastError);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	/*
		No longer need server socket
	*/
	closesocket(serverSocket);

	/*
		Receive until peers shutdown
	*/
	do {
		iResult = recv(clientSocket, recvBuf, recvBufLen, 0);
		if (iResult > 0) {
			printf("Bytes Received %d\n", iResult);

			/*
				Echo the buffer back to the user
			*/
			iSendResult = send(clientSocket, recvBuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("Send failed with error: %ld\n", WSAGetLastError());
				closesocket(clientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes Sent: %d\n", iSendResult);
		}
		else if (iResult == 0) {
			printf("Connection Closing...\n");
		}
		else {
			printf("recv failed with error %ld\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);

	/*
		shutdown the connection
	*/
	iResult = shutdown(clientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("Shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	/*
		Cleanup
	*/
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}