#ifndef SFML_H
#define SFML_H
#include <SFML/Network.hpp>

using namespace std;

//fungsi TCP socket connect dari Header SFML/Network.hpp
static bool checking(const string address, int port)
{
	sf::Time Timeout = sf::milliseconds(300);
	return (sf::TcpSocket().connect(address, port, Timeout) == sf::Socket::Done);
}
#endif