#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

DWORD dwGetModuleBaseAddress(DWORD dwProcessIdentifier, TCHAR *lpszModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessIdentifier);
	DWORD dwModuleBaseAddress = 0;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}

INT czytaj(HANDLE uchwytz, DWORD bazowyadres, DWORD statyk, DWORD ofsetz)
{
	//int px;
	//ReadProcessMemory(uchwytz, (LPCVOID)adr, &px, sizeof(px), NULL);


	DWORD adresik;
	DWORD rozmiar2;
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik += ofsetz;			//dodaj ofset
	int kupka;					// deklaracja wyniku
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &kupka, sizeof(int), &rozmiar2); // czytaj wynik
	return kupka;  //oddaj kupke


}

VOID zapisz(HANDLE chwyt, DWORD adressik, DWORD statyk, DWORD ofsetx, int ileHp)
{

	DWORD adresik;
	DWORD rozmiar2;
	ReadProcessMemory(chwyt, (LPCVOID)(adressik + statyk), &adresik, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik += ofsetx;			//dodaj ofset
	WriteProcessMemory(chwyt, (void*)adresik, &ileHp, sizeof(ileHp), &rozmiar2);
	if (!WriteProcessMemory)
	{
		cout << "dupa" << endl;
	}
	//WriteProcessMemory(hProcess, (void*)Offset, &data, dataSize, 0);
}

int main()
{
	// poczatek
	HWND okno = FindWindow(0, _TEXT("Gothic II - 2.6 (pol)")); // nazwa okna
	if (okno == 0) {
		printf("niema okna\n");
		char f;
		cin >> f;
		return 0;
	}

	DWORD pID = 0;
	GetWindowThreadProcessId(okno, &pID);

	DWORD baza = dwGetModuleBaseAddress(pID, _T("Gothic2.exe"));  // nazwa procesu
	DWORD bazaOfset = 0x42990C;
	DWORD innyOfset = 0x420000;
	HANDLE uchwyt = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	// koniec poczatka


	//ofsety

	DWORD ofsetHP = 0x1b8;
	DWORD ofsetMaxHP = 0x1bc;
	DWORD ofsetAktualnaMana = 0x1c0;  //ofsety ida do gory 0 - 4 - 8 - c
	DWORD ofsetMaxMana = 0x1c4;
	DWORD ofsetCos1 = 0x1c8;
	DWORD ofsetCos2 = 0x1cc;
	DWORD ofsetCos3 = 0x1d0;



	// po ofsetach





	//DWORD baza = 0;

	while (1) {

		if (GetAsyncKeyState(VK_INSERT)) {
			// insert

			system("cls");
			int pz; // tyle mam hp
			int elo; // tyle chce hp
			cout << "Podaj ile chcesz zycia" << endl;
			Sleep(1000);
			//pz = czytaj(uchwyt, kaka[0]);
			cin >> elo;

			pz = czytaj(uchwyt, baza, bazaOfset, ofsetHP); // czytaj


			zapisz(uchwyt, baza, bazaOfset, ofsetHP, elo);
			//if (!zapisz)

			//{
			//	cout << "nunu" << endl; 
			//}

			cout << endl;
			cout << "Miales " << pz << " zycia" << endl;
			cout << "Zmieniles na " << elo << " zycia" << endl;
			Sleep(1000);

			// koniec inserta
		}
		else if (GetAsyncKeyState(VK_END)) {
			//end
			system("cls");
			cout << "end" << endl;
			Sleep(1000);

			//koniec enda
		}
		else if (GetAsyncKeyState(VK_LSHIFT)) {
			//lewyszift zamyka

			system("cls");
			cout << "Zamykam." << endl;
			Sleep(1000);

			return 0;

			//koniec lewegoszifta
		}

		else if (GetAsyncKeyState(VK_HOME)) {
			//home pokazue hp

			int pz = czytaj(uchwyt, baza, bazaOfset, ofsetHP);
			while (pz != 0) {
				system("cls");

				int elo;
				cout << "###########################" << endl;
				cout << "#                         #" << endl;
				cout << "#                         #" << endl;
				cout << "#       " << pz << "               #" << endl;
				cout << "#                         #" << endl;
				cout << "#                         #" << endl;
				cout << "###########################" << endl;



				//zapisz(uchwyt, baza, bazaOfset, ofsetHP, elo);
				//if (!zapisz)

				//{
				//	cout << "nunu" << endl; 
				//}

			}

			//koniec home
		}




	}
}