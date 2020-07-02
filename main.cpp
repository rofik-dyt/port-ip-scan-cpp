
#include <iostream>
#include <sstream>
#include <SFML/Network.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <conio.h>

#pragma warning (disable : 4996)

using namespace std;

static bool checking(const string address, int port)
{
	sf::Time Timeout = sf::milliseconds(500);
	return (sf::TcpSocket().connect(address, port, Timeout) == sf::Socket::Done);
}

void Scan(string Address, int portNumber, int ID)
{
	if (checking(Address, portNumber)) {
		if (ID == 1)
			cout << "OPEN" << endl;
		else if (ID == 2)
			cout << "Alive" << endl;
	}

	else {
		if (ID == 1)
			cout << "CLOSED" << endl;
		else if (ID == 2)
			cout << "DEAD" << endl;
	}
}


int main()
{
	int mainMenu;

	cout << "1.port scan" << endl;
	cout << "2.ip scan" << endl;
	cout << "Pilih : "; cin >> mainMenu;
	
	//Port Scan
	if (mainMenu == 1)
	{
		string ipAddress;
		int startPort, endPort, PortClosed;

		cout << "Masukkan IP Address/DNS : "; cin >> ipAddress;
		cout << "Masukkan range port awal : "; cin >> startPort;
		cout << "Masukkan range port akhir : "; cin >> endPort;

		for (int i = startPort; i <= endPort; i++)
		{
			cout << "Port " << i << " : ";
			Scan(ipAddress, i, 1);
		}

		//cout << "Jumlah port kosong " << PortClosed;
	}

	//IP Scan
	else if (mainMenu == 2)
	{
		char ipAddress[17] = "";
		string strIpAddress;
		int startSubnet, endSubnet;

		cout << "Masukkan IP address : ";
		cin >> ipAddress;

		cout << "Masukkan Batas subnet terakhir : ";
		cin >> endSubnet;

		//get Start Address
		char* token = strtok(ipAddress, ".");
		vector<int> ipBlock;

		while (token != NULL)
		{
			ipBlock.push_back(strtol(token, NULL, 10));
			token = strtok(NULL, ".");
		}
		startSubnet = ipBlock[3];


		for (int i = 0; i < 3; i++)
		{
			//convert IpAddress	Int to String and Rebuild
			ostringstream stringConvert;
			stringConvert << ipBlock[i];
			strIpAddress += stringConvert.str();
			strIpAddress += ".";
		}


		for (int i = startSubnet; i <= endSubnet; i++)
		{

			//convert int to string last subnet
			ostringstream stringConvert;
			stringConvert << i;
			string endSubnet = stringConvert.str();

			//append string
			string ipRan = strIpAddress + endSubnet;

			//proses
			cout << "IP " << ipRan << " : ";
			Scan(ipRan, 22, 2);
		}
	}
	getch();
}

