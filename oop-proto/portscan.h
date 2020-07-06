#include "sfml-network.h"

using namespace std;

struct PortData
{
	int* openPort = new int[65535];
	//int openPort[65535];
	int countPort = 0;
	int closedPort = 0;

}PORT;


int ScanningPort(string ipAddress, int port)
{
	if (checking(ipAddress, port))
	{
		PORT.openPort[PORT.countPort] = port;
		PORT.countPort += 1;
	}
	else
	{
		PORT.closedPort += 1;
	}
}

void ResultPort()
{
	//system("cls");
	cout << "-------------------------------" << endl;
	cout << "Proses Scanning Selesai\n" << endl;

	
	
	//tampilkan PORT yang terbuka
	for (int i = 0; i < PORT.countPort; i++)
	{
		cout << "PORT " << PORT.openPort[i] << " : OPEN\n";
		
	}

	//tampilkan PORT yang tertutup
	cout << "-------------------------------" << endl;
	cout << "Jumlah port yang tertutup : " << PORT.closedPort << endl;

	//reset values
	//delete[] PORT.openPort;
	//for (int i = 0; i < PORT.countPort; i++)
	//{
		//delete[i] PORT.openPort;
	//}
}
