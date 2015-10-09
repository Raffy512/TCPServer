#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")


void Server()
{
	int Result;
	WSADATA data;
	if (WSAStartup(WORD(2.2), &data) != 0)
	{
		std::cout << "Error: Initializing Failed" << std::endl;
		return;
	}
	std::cout << "Initializing Complete" << std::endl;

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	std::cout << "Socket Created" << std::endl;

	sockaddr_in service;

	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(8080);

	Result = bind(Socket, (SOCKADDR *)&service, sizeof(service));
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Bind failed" << std::endl;
		//closesocket(Socket);
		return;
	}
	else
	{
		std::cout << "Succesfully binded" << std::endl;
	}

	if (listen(Socket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Listen Failed" << std::endl;
	}
	else
	{
		std::cout << "Succesfully listening" << std::endl;
	}

	SOCKET AcceptSocket;

	std::cout << "AcceptSocket Created" << std::endl;

	AcceptSocket = accept(Socket, NULL, NULL);

	if (AcceptSocket == INVALID_SOCKET)
	{
		std::cout << "accept Failed" << std::endl;

	}
	else
	{
		std::cout << "Connection Accepted" << std::endl;
	}


	if (send(AcceptSocket, "homo", 4, NULL) == SOCKET_ERROR)
	{
		std::cout << "Sending failed" << std::endl;
	}
	else
	{
		std::cout << "Data send" << std::endl;
	}

	closesocket(Socket);


	if (shutdown(AcceptSocket, SD_BOTH) == SOCKET_ERROR)
	{
		std::cout << "shutdown failed" << std::endl;

	}
	else
	{
		std::cout << "shutdown successfull" << std::endl;
	}

	char a;
	std::cin >> a;
	return;

}

void Client()
{
	int Result;
	WSADATA data;
	if (WSAStartup(WORD(2.2), &data) != 0)
	{
		std::cout << "Error: Initializing Failed" << std::endl;
		return;
	}
	std::cout << "Initializing Complete" << std::endl;

	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	std::cout << "ClientSocket Created" << std::endl;

	sockaddr_in Clientservice;


	Clientservice.sin_family = AF_INET;
	Clientservice.sin_addr.s_addr = inet_addr("104.28.16.24");
	Clientservice.sin_port = htons(80);

	Result = connect(ClientSocket, (SOCKADDR*)&Clientservice, sizeof(Clientservice));

	if (Result == SOCKET_ERROR)
	{
		std::cout << "Connection failed" << std::endl;
	}
	else
	{
		std::cout << "Connected" << std::endl;
	}

	char* Httpheader = "GET /1405/hahaha-du-bist-lustig--doch-toete-ich-zuletzt.jpg HTTP/1.1\r\nHost: pix.echtlustig.com\r\nAccept: image/jpeg\r\n\r\n";

	Result = send(ClientSocket, Httpheader, (int)strlen(Httpheader), 0);	
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Send Failed" << std::endl;
	}
	else
	{
		std::cout << "Send ok" << std::endl;
	}
	char value[509597];

	Result = recv(ClientSocket, value, sizeof(value), 0);
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Nothing recieved" << std::endl;
	}
	else
	{
		std::cout << value << std::endl;
	}

	char a;
	std::cin >> a;
	return;



}

void main()
{
	//Server();
	Client();

}