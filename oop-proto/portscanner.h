#pragma once
#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

static bool checking(const string address, int port)
{
	sf::Time Timeout = sf::milliseconds(500);
	return (sf::TcpSocket().connect(address, port, Timeout) == sf::Socket::Done);
}

void Scanning(string ipAddress, int startPort, int endPort)
{


	for (int i = startPort; i <= endPort; i++)
	{
		if (checking(ipAddress, i))
		{
			cout << "Port " << i << " : ";
			cout << "OPEN" << endl;
		}
	}
}

