
#include <iostream>
#include <string>
#include <windows.h>
#include "portscan.h"
#include "ipscan.h"
//#include <malloc.h>

int main()
{
MAINMENU:

	char mainMenu;

	cout << ">>> Pilih Menu<<<" << endl;
	cout << "1.Port Scanner" << endl;
	cout << "2.IP Scanner" << endl;
	cout << "3.Keluar Program" << endl;
	cout << "\nPilih : "; cin >> mainMenu;

	if (mainMenu == '1')
	{
	SCANPORT:

		string ipAddress;
		int startPort, endPort;
		int backMenu;

		cout << "-------------------------------" << endl;
		cout << "----------PORT SCANNER---------" << endl;
		cout << "-------------------------------" << endl;
		cout << endl;

		cout << "Masukkan IP Address/DNS : "; cin >> ipAddress;
		cout << "Masukkan range port awal : "; cin >> startPort;
		cout << "Masukkan range port akhir : "; cin >> endPort;
		
		//proses scanning
		for (int i = startPort; i <= endPort; i++)
		{
			ScanningPort(ipAddress, i);
		}
		//menampilkan hasil scanning
		ResultPort();

		
		//cout << "1. ulang\n";
		//cout << "2. menu\n";
		//cout << "pilih : ";
		//cin >> backMenu;
		//if (backMenu == 1)
		//	goto SCANPORT;
		
	}

	else if (mainMenu == '2')
	{
	SCANIP:

		char ipAddress[15] = "";
		string strAddress;
		int startSubnet = 0;
		int endSubnet = 0;
		int backMenu;

		cout << "-------------------------------" << endl;
		cout << "-----------IP SCANNER----------" << endl;
		cout << "-------------------------------" << endl;
		cout << endl;

		cout << "Masukkan IP address : "; cin >> ipAddress;
		cout << "Masukkan Batas subnet terakhir : "; cin >> endSubnet;
		cout << endl;

		char* token = strtok(ipAddress, ".");
		vector<int> ipBlock;

		while (token != NULL)
		{
			ipBlock.push_back(strtol(token, NULL, 10));
			token = strtok(NULL, ".");
		}
		startSubnet = ipBlock[3];

		// convert IpAddress	Int to String and Rebuild
		for (int i = 0; i < 3; i++)
		{
			strAddress += ConvertIntToString(ipBlock[i], 1);
		}

		ScanningAddress(strAddress, startSubnet, endSubnet);
		ResultAddress();

	}
}
