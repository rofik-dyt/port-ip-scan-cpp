#pragma warning (disable : 4996)
#include <vector>
#include <sstream>
#include "sfml-network.h"

using namespace std;

//structur untuk menyimpan hasil scanning
struct DataAddress
{
	char aliveAddress[255][16];
	int deadAddress;
	int count;
	int lenghtAddress[255];
}ADDRESS;


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

//fungsi untuk melakukan scanning ip address
int ScanningAddress(string ipAddress, int startSubnet, int endSubnet)
{
	int tempCountAdd = 0;
	for (int i = startSubnet; i <= endSubnet; i++)
	{
		system("cls");
		cout << "\t\t\tTunggu Bentar" << endl;
		cout << "Program sedang melakukan Scanning..........\n\n";
		cout << tempCountAdd << " Address terscan";
		
		//mendapatkan alamat terakhir
		string lastSubnet = ConvertIntToString(i, 2);
		string strAddress = ipAddress + lastSubnet;

		//menghitung panjang karakter dari string ipAddress
		int countIndex = strAddress.size();

		if (checking(strAddress, 22))
		{
			char bitAddress[15];

			//Simpan IP Alive ke Array
			strcpy(bitAddress, strAddress.c_str());
			strcpy(ADDRESS.aliveAddress[ADDRESS.count], bitAddress);

			//Simpan panjang String ke Array
			ADDRESS.lenghtAddress[ADDRESS.count] = countIndex;

			//menghitung address yang ONLINE
			ADDRESS.count += 1;
		}

		else
		{
			//Port SMB windows
			if (checking(strAddress, 445))
			{
				char bitAddress[15];

				//Simpan IP Alive ke Array
				strcpy(bitAddress, strAddress.c_str());
				strcpy(ADDRESS.aliveAddress[ADDRESS.count], bitAddress);

				//Simpan panjang tiap String ke Array
				ADDRESS.lenghtAddress[ADDRESS.count] = countIndex;

				//menghitung address yang ONLINE
				ADDRESS.count += 1;
			}
			else
			{
				//menghitung address yang OFFLINE
				ADDRESS.deadAddress += 1;
			}
		}
		
		//Menghitung total addres yang terscan
		tempCountAdd +=1 ;
	}
	return 0;
}

//fungsi untuk menampilkan hasil dari scanning
void ResultAddress()
{
	//tampilkan Address yang Hidup/ONLINE, yang tersimpan pada struct
	for (int i = 0; i < ADDRESS.count; i++)
	{
		cout << "IP ";
		int addressColm = ADDRESS.lenghtAddress[i];

		for (int j = 0; j < addressColm; j++)
		{
			cout << ADDRESS.aliveAddress[i][j];
		}
		cout << " : Online" << endl;
	}
	
	//tampilkan ip yg mati
	cout << "-------------------------------" << endl;
	cout << "Jumlah IP yang Offline : " << ADDRESS.deadAddress << endl;

	//reset values
	ADDRESS.count = 0;
	ADDRESS.deadAddress = 0;
}