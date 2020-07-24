
#include <iostream>
#include <sstream>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <windows.h>

#pragma warning (disable : 4996)

using namespace std;

//fungsi TCP socket connect dari Header SFML/Network.hpp
static bool checking(const string address, int port)
{
	sf::Time Timeout = sf::milliseconds(300);
	return (sf::TcpSocket().connect(address, port, Timeout) == sf::Socket::Done);
}


//fungsi convert int to string
string ConvertIntToString(int i, int id)
{
	string streamString;
	ostringstream stringConvert;

	stringConvert << i;
	streamString += stringConvert.str();

	if (id == 1)
		streamString += ".";

	return streamString;
}

void headPort()
{
	cout << "-------------------------------" << endl;
	cout << "----------PORT SCANNER---------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}

void headAddress()
{
	cout << "-------------------------------" << endl;
	cout << "-----------IP SCANNER----------" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
}

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

MainMenu:
	char mainMenu;

	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "==================================" << endl;
	cout << "--------___________________-------" << endl;
	cout << "-------| Port & IP Scanner |------" << endl;
	cout << "----------------------------------" << endl;
	cout << "==================================" << endl;
	cout << "\n";

	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << ">>> Pilih Menu<<<" << endl;
	cout << "1. Port Scanner" << endl;
	cout << "2. IP Scanner" << endl;
	cout << "3. Keluar Program" << endl;
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\nPilih : "; cin >> mainMenu;

	system("cls");

	switch (mainMenu)
	{
	//Port Scan
	case '1':
	{
	ScanPort:
		string ipAddress;
		int startPort = 0, endPort = 0;
		int closedPort = 0;
		int backMenu;
		int countPort = 0;
		int openPort[65535];

		headPort();

		cout << "Masukkan IP Address/DNS : "; cin >> ipAddress;
		cout << "Masukkan range port awal : "; cin >> startPort;
		cout << "Masukkan range port akhir : "; cin >> endPort;
		cout << endl;

		//proses scanning port
		int tempCountPort = 0;
		for (int i = startPort; i <= endPort; i++)
		{
			
			system("cls");
			headPort();
			cout << "			Tunggu Bentar		" << endl;
			cout << "Program sedang melakukan Scanning..........\n\n";
			cout << tempCountPort << " Port terscan";

			if (checking(ipAddress, i))
			{
				openPort[countPort] = i;
				countPort += 1;
			}
			else
				closedPort += 1;

			tempCountPort += 1;
		}


		system("cls");
		headPort();

		cout << "-------------------------------" << endl;
		cout << "	Proses Scanning Selesai\n" << endl;
		cout << "-------------------------------" << endl;

		//tampilkan PROT yang terbuka
		for (int i = 0; i < countPort; i++)
		{
			cout << "PORT " << openPort[i] << " : OPEN\n";
		}

		//tampilkan total port yg tertutup
		cout << "-------------------------------" << endl;
		cout << "Jumlah port yang tertutup : " << closedPort << endl;

		//return ke menu
	returnPort:
		cout << "-------------------------------" << endl;
		cout << "1. Untuk kembali melakukan scanning" << endl;
		cout << "2. Untuk kembali ke menu awal" << endl;

		cout << "\nPilih : "; cin >> backMenu;
		if (backMenu == 1)
		{
			system("cls");
			goto ScanPort;

		}
		else if (backMenu == 2)
		{
			system("cls");
			goto MainMenu;
		}
		else
		{
			cout << "\nFormat Inputan Salah...";
			Sleep(3000);
			system("exit");
		}
		break;
	}

	//IP Scan
	case '2':
	{
	ScanIP:
		char ipAddress[15] = "";
		char aliveAddress[255][15];
		string strIpAddress;
		int startSubnet = 0, endSubnet = 0;
		int deadAddress = 0;
		int count = 0;
		int lenghtAddress[255];
		int backMenu;

		headAddress();

		cout << "Masukkan IP address : "; cin >> ipAddress;
		cout << "Masukkan Batas subnet terakhir : "; cin >> endSubnet;
		cout << endl;

		//get Start Address dengan memecah menggunakan vektor int
		char* token = strtok(ipAddress, ".");
		vector<int> ipBlock;

		while (token != NULL)
		{
			ipBlock.push_back(strtol(token, NULL, 10));
			token = strtok(NULL, ".");
		}
		startSubnet = ipBlock[3];

		//convert IpAddress	Int to String and Rebuild
		for (int i = 0; i < 3; i++)
		{
			strIpAddress += ConvertIntToString(ipBlock[i], 1);
		}

		int tempCountAdd = 0;

		//Perulangan Last Subnet (Proses Scanning)
		for (int i = startSubnet; i <= endSubnet; i++)
		{
			system("cls");
			headAddress();

			cout << "Program sedang melakukan Scanning..........\n\n";
			cout << tempCountAdd << " Address terscan";

			//convert int to string last subnet
			string endSubnet = ConvertIntToString(i, 2);

			//append string
			string ipRan = strIpAddress + endSubnet;

			int countIndex = ipRan.size();


			//Trying Connect to IP and PORT
			//Port SSH
			if (checking(ipRan, 22))
			{
				char bit[17];

				//Simpan IP Alive ke Array
				strcpy(bit, ipRan.c_str());
				strcpy(aliveAddress[count], bit);

				//Simpan panjang tiap String ke Array
				lenghtAddress[count] = countIndex;

				count += 1;
			}
			else
			{
				//Port SMB windows
				if (checking(ipRan, 445))
				{
					char bit[15];

					//Simpan IP Alive ke Array
					strcpy(bit, ipRan.c_str());
					strcpy(aliveAddress[count], bit);

					//Simpan panjang tiap String ke Array
					lenghtAddress[count] = countIndex;

					count += 1;
				}

				else
				{
					deadAddress += 1;
				}

			}
			tempCountAdd += 1;
		}
		system("cls");
		headAddress();

		cout << "-------------------------------" << endl;
		cout << "Proses Scanning Selesai\n" << endl;

		//tampilkan IP yang hidup
		for (int i = 0; i < count; i++)
		{
			cout << "IP ";
			int addressColm = lenghtAddress[i];

			for (int j = 0; j < addressColm; j++)
			{
				cout << aliveAddress[i][j];
			}
			cout << " : Online" << endl;
		}

		//tampilkan ip yg mati
		cout << "-------------------------------" << endl;
		cout << "Jumlah IP yang Offline : " << deadAddress << endl;

		//return ke menu
		cout << "-------------------------------" << endl;
		cout << "\n";

		cout << "1. Untuk kembali melakukan scanning" << endl;
		cout << "2. Untuk kembali ke menu awal" << endl;
		cout << "\nPilih : "; cin >> backMenu;
		if (backMenu == 1)
		{
			system("cls");
			goto ScanIP;

		}
		else if (backMenu == 2)
		{
			system("cls");
			goto MainMenu;
		}
		else
		{
			cout << "\nFormat Inputan Salah...";
			Sleep(3000);
			system("exit");
		}

		break;
	}
	case '3':
		system("exit");
		break;

	default:
		goto MainMenu;
		break;
	}
}
