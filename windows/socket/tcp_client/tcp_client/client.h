/**
* \file client_main.cpp
* \brief TCP client transfers
* \author Gilson Varghese <gilsonvarghese7@gmail.com>
* \date June 20 2017
*/

#ifndef TCP_CLIENT
#define TCP_CLIENT

/*
	Added to avoid redefinition error
	As per http://www.zachburlingame.com/2011/05/resolving-redefinition-errors-betwen-ws2def-h-and-winsock-h/
*/
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "28000"

/*
	Fuinction declarations
*/
int startClient();

#endif