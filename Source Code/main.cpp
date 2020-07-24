#include <iostream>
#include <string>
#include <windows.h>
#include "portscan.h"
#include "ipscan.h"

using namespace std;

void portLabel()
{
	cout << "-------------------------------" << endl;
	cout << "----------PORT SCANNER---------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}

void addressLabel()
{
	cout << "-------------------------------" << endl;
	cout << "-----------IP SCANNER----------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}

void endLabel()
{
		cout << "-------------------------------" << endl;
		cout << "    Proses Scanning Selesai\n" << endl;
		cout << "-------------------------------" << endl;
}

int main()
{
MAINMENU:
	char mainMenu;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "==================================" << endl;
	cout << "--------___________________-------" << endl;
	cout << "-------| Port & IP Scanner |------" << endl;
	cout << "----------------------------------" << endl;
	cout << "==================================" << endl;
	cout << "\n";

	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << ">>> Pilih Menu<<<" << endl;
	cout << "1.Port Scanner" << endl;
	cout << "2.IP Scanner" << endl;
	cout << "3.Keluar Program" << endl;

	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\nPilih : "; cin >> mainMenu;

	if (mainMenu == '1')
	{
	SCANPORT:
		system("cls");

		string ipAddress;
		int startPort, endPort;
		int backMenu;

		portLabel();
		cout << "Masukkan IP Address/DNS : "; cin >> ipAddress;
		cout << "Masukkan range port awal : "; cin >> startPort;
		cout << "Masukkan range port akhir : "; cin >> endPort;
		
		//proses scanning
		int tempCountPort = 0;
		for (int i = startPort; i <= endPort; i++)
		{
			system("cls");
			portLabel();
			cout << "\t\t\tTunggu Bentar" << endl;
			cout << "Program sedang melakukan Scanning..........\n\n";
			cout << tempCountPort << " Port terscan";

			ScanningPort(ipAddress, i);

			//menghitung Porrt yang telah terscan
			tempCountPort +=1;
		}

		//menampilkan hasil scanning
		system("cls");
		ResultPort();

		
		cout << "1. Untuk kembali melakukan scanning" << endl;
		cout << "2. Untuk kembali ke menu awal" << endl;
		cout << "\nPilih : "; cin >> backMenu;

		if (backMenu == 1)
		{
			system("cls");
			goto SCANPORT;

		}
		else if (backMenu == 2)
		{
			system("cls");
			goto MAINMENU;
		}
		else
		{
			cout << "\nFormat Inputan Salah...";
			Sleep(3000);
			system("exit");
		}
	}


	else if (mainMenu == '2')
	{
	SCANIP:
		system("cls");

		char ipAddress[15] = "";
		string strAddress;
		int startSubnet = 0;
		int endSubnet = 0;
		int backMenu;

		addressLabel();
		cout << "Masukkan IP address : "; cin >> ipAddress;
		cout << "Masukkan Batas subnet terakhir : "; cin >> endSubnet;
		cout << endl;

		//Pecah IP Address menjadi block 
		char* token = strtok(ipAddress, ".");
		vector<int> ipBlock;
		while (token != NULL)
		{
			ipBlock.push_back(strtol(token, NULL, 10));
			token = strtok(NULL, ".");
		}

		//mendapatkan address pertama yang akan di scan
		startSubnet = ipBlock[3];

		//convert IpAddress Int to String dengan memanggil fungsi Convert pada ipscan.h
		for (int i = 0; i < 3; i++)
		{
			strAddress += ConvertIntToString(ipBlock[i], 1);
		}

		//Memanggil fungsi scanning pada ipscan.h
		ScanningAddress(strAddress, startSubnet, endSubnet);

		system("cls");
		endLabel();

		//memanggil fungsi untuk menampilkan hasil scanning
		ResultAddress();

		cout << "1. Untuk kembali melakukan scanning" << endl;
		cout << "2. Untuk kembali ke menu awal" << endl;
		cout << "\nPilih : "; cin >> backMenu;

		if (backMenu == 1)
		{
			system("cls");
			goto SCANIP;

		}
		else if (backMenu == 2)
		{
			system("cls");
			goto MAINMENU;
		}
		else
		{
			cout << "\nFormat Inputan Salah...";
			Sleep(3000);
			system("exit");
		}
	}
}
