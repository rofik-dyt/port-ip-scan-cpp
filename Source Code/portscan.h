#include "sfml-network.h"

using namespace std;

//structur untuk menyimpan hasil scanning
struct PortData
{
	int openPort[65535];
	int countPort;
	int closedPort;

}PORT;

//fungsi untuk melakukan scanning Port
int ScanningPort(string ipAddress, int port)
{
	//Jika port terbuka
	if (checking(ipAddress, port))
	{
		PORT.openPort[PORT.countPort] = port;
		PORT.countPort += 1;
	}

	//Jika port tertutup
	else
	{
		PORT.closedPort += 1;
	}
	return 0;
}

//fungsi untuk menampilkan hasil scanning yang disimpan pada struct
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
	PORT.closedPort = 0;
	PORT.countPort = 0;
}
