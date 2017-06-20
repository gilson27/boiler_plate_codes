/**
 * \file server.h
 * \brief Server declarations
 * \author Gilson Varghese <gilsonvarghese7@gmail.com>
 * \date June 19 2017
*/

#ifndef TCP_SERVER
#define TCP_SERVER

/*
	Added to avoid redefinition error () 
	As per http://www.zachburlingame.com/2011/05/resolving-redefinition-errors-betwen-ws2def-h-and-winsock-h/
 */
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "28000"

/*
	Function declaration
*/

int startServer();

#endif