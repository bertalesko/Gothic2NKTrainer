#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <time.h>
#include <tchar.h>

using namespace std;


// funkcje


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

INT czytajINT(HANDLE uchwytz, DWORD bazowyadres, DWORD statyk, DWORD ofsetz)
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

VOID piszHP(HANDLE chwyt, DWORD adressik,DWORD ofsetHp, int ileHp)
{

	DWORD adresik;
	DWORD rozmiar2;
	ReadProcessMemory(chwyt, (LPCVOID)(adressik + ofsetHp), &adresik, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik += 0x1b8;			//dodaj ofset
	WriteProcessMemory(chwyt, (void*)adresik, &ileHp, sizeof(ileHp), &rozmiar2);
	if (!WriteProcessMemory)
	{
		cout << "dupa" << endl;
	}
	//WriteProcessMemory(hProcess, (void*)Offset, &data, dataSize, 0);
}

int czytajHp(HANDLE uchwytz,DWORD statyk, DWORD bazowyadres)
{
	//int px;
	//ReadProcessMemory(uchwytz, (LPCVOID)adr, &px, sizeof(px), NULL);


	DWORD adresik;
	DWORD rozmiar2;
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik += 0x1b8;			//dodaj ofset
	int kupka;					// deklaracja wyniku
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &kupka, sizeof(int), &rozmiar2); // czytaj wynik
	return kupka;  //oddaj kupke


}

float czytajTymczas(HANDLE uchwytz, DWORD statyk, DWORD bazowyadres)
{
	


	DWORD adresik;
	DWORD rozmiar2;
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik, sizeof(float), &rozmiar2); // czytaj 1wszy adres
	adresik += 0x66c;			//ofset1
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &adresik, sizeof(int), &rozmiar2); // czytaj wynik
	adresik += 0x1c;			//ofset2
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &adresik, sizeof(int), &rozmiar2); // czytaj wynik
	adresik += 0x204;			//ofset3
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &adresik, sizeof(int), &rozmiar2); // czytaj wynik
	adresik += 0x68;				//ofset4
			//ostatni ofset
	float pozycjaT;     // deklaracja 
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &pozycjaT, sizeof(int), &rozmiar2); // czytaj wynik
	return pozycjaT;  //oddaj pozycjeZ


}


float czytajLokacje(HANDLE uchwytz, DWORD statyk, DWORD bazowyadres, DWORD ofset)
{

	DWORD adresik;
	DWORD rozmiar2;
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik, sizeof(float), &rozmiar2); // czytaj 1wszy adres
	adresik += ofset;			//ofset1
	float pozycjaT;     // deklaracja 
	ReadProcessMemory(uchwytz, (LPCVOID)adresik, &pozycjaT, sizeof(int), &rozmiar2); // czytaj wynik
	return pozycjaT;  //oddaj pozycjeZ
	if (bazowyadres==NULL)
	{
		pozycjaT = 0;
	}
	return pozycjaT;  //oddaj pozycjeZ


}

void piszLokacje(HANDLE uchwytz,DWORD bazowyadres, DWORD statyk,DWORD ofsetX,DWORD ofsetY, DWORD ofsetZ)
{
	//int px;
	//ReadProcessMemory(uchwytz, (LPCVOID)adr, &px, sizeof(px), NULL);


	DWORD adresik1;
	DWORD adresik2;
	DWORD adresik3;
	DWORD rozmiar2;
	
	float noweZ;
	float noweX;
	float noweY;
	cout << "Podaj nowe Z" << endl;
	cin >> noweZ;
	cout << "Podaj nowe X" << endl;
	cin >> noweX;
	cout << "Podaj nowe Y" << endl;
	cin >> noweY;
	//pisze X
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik1, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik1 += ofsetX;
	WriteProcessMemory(uchwytz, (LPCVOID*)adresik1, &noweX, sizeof(float), &rozmiar2);
	if (!WriteProcessMemory)
	{
		cout << "Klaps" << endl;
	}
	//pisze Y
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik2, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik2 += ofsetY;
	WriteProcessMemory(uchwytz, (LPCVOID*)adresik2, &noweY, sizeof(float), &rozmiar2);
	if (!WriteProcessMemory)
	{
		cout << "Klaps" << endl;
	}
	//pisze Z
	ReadProcessMemory(uchwytz, (LPCVOID)(bazowyadres + statyk), &adresik3, sizeof(DWORD), &rozmiar2); // czytaj 1wszy adres
	adresik3 += ofsetZ;
	WriteProcessMemory(uchwytz, (LPCVOID*)adresik3, &noweZ, sizeof(float), &rozmiar2);
	if (!WriteProcessMemory)
	{
		cout << "Klaps" << endl;
	}
}


void piszLokacje2(HANDLE uchwytz, DWORD bazowyadres, DWORD statykz, DWORD statyky, DWORD statykx)
{
	//int px;
	//ReadProcessMemory(uchwytz, (LPCVOID)adr, &px, sizeof(px), NULL);


	DWORD adresik;
	DWORD rozmiar2;

	float noweZ = 6666;
	float noweX = 3;
	float noweY = 3;
	
	WriteProcessMemory(uchwytz, (LPCVOID*)bazowyadres + statykz, &noweZ, sizeof(float), &rozmiar2);
	if (!WriteProcessMemory)
	{
		cout << "Klaps" << endl;
	}
	WriteProcessMemory(uchwytz, (LPCVOID*)bazowyadres + statyky, &noweY, sizeof(float), &rozmiar2);
	WriteProcessMemory(uchwytz, (LPCVOID*)bazowyadres + statykx, &noweX, sizeof(float), &rozmiar2);



}

BOOL jestOkno(string Ltytul)
{
	bool wyjscie;
	LPCSTR Ltyteks = Ltytul.c_str();
	HWND okienko;
		 okienko= FindWindowA( NULL, Ltyteks);
	if (!okienko)
	{
		wyjscie = 0;
	}
	else
	{
		wyjscie = 1;
	}
	return wyjscie;
}


// po funkcjach


	//ofsety
	DWORD ofsetBaza = 0x42990C;  // ofset bazowy
	DWORD ofsetX = 0x48;
	DWORD ofsetY = 0x68;
	DWORD ofsetZ = 0x58;
	DWORD ofsetAktualneHP = 0x1b8;
	DWORD ofsetMaxHP = 0x1bc;
	DWORD ofsetAktualnaMana = 0x1c0;  //ofsety ida do gory 0 - 4 - 8 - c
	DWORD ofsetMaxMana = 0x1c4;
	DWORD ofsetSila = 0x1c8;
	DWORD ofsetAgi = 0x1cc;
	DWORD ofsetBronie1H = 0x1dc;
	DWORD ofsetBronie2h = 0x1e0;
	DWORD ofsetLuki = 0x1e4;
	DWORD ofsetKusze = 0x1e8;
	DWORD ofsetWymaganyExp = 0x430;
	DWORD ofsetAktualnyExp = 0x42c;
	DWORD ofsetPunktyNauki = 0x434;
	DWORD ofsetIDPostaci = 0x120;
	DWORD ofsetOchronaPociski = 0x204;
	DWORD ofsetOchronaMagia = 0x200;
	DWORD ofsetOchronaSmoczyOgien = 0x1f8;
	DWORD ofsetOchronaBron = 0x23c;



	
	// po ofsetach
	

	//dodatkowe
	bool jestGra;
	bool rysowac = true;
	bool hp=false;
	bool nowaLokacja = false;

	

	//po dodatkowych


int main()
{
	int czasOstatnieOdswiezenie = clock();
	int czasOdStartu = clock();
	int blokada;
	HWND okno = NULL;//FindWindow(0, _TEXT("Gothic II - 2.6 (pol)")); // nazwa okna

	DWORD pID = 0;
	
	int zapis;

	DWORD baza = NULL;
	char d[256];
	DWORD statykHp = 0x42990C;
	HANDLE uchwyt = NULL;// OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	//bool jestGra = jestOkno("Gothic II - 2.6 (pol)");
	string napisHp;
	napisHp = "Nieaktywne";
	string stanGry;
	stanGry = "Czekam na gre";
	int iloscHp;
	int czasek = clock();
	float napisZ = 0;
	float napisY=0;
	float napisX=0;
	int napisPN = 0;
	int napisEXP = 0;
	int napisOchrona1 = 0;
	int napisOchrona2 = 0;
	int napisOchrona3 = 0;
	int napisOchrona4 = 0;
	int napisKusze = 0;
	int napisLuki = 0;
	int napisBronie1h = 0;
	int napisBronie2h = 0;


	string zmienia;
	int f; // do switcha dla eycji statow

	
	

	// koniec poczatka



	while (!GetAsyncKeyState(VK_END))
	{

		if (clock() - czasOdStartu > 100)  // sprawdza czy jest gra i zmienia napisy stanu gry
		{
			czasOdStartu = clock(); 
			jestGra = false;
			okno = FindWindow(0, _TEXT("Gothic II - 2.6 (pol)")); // nazwa okna
			if (okno)
			{
				GetWindowThreadProcessId(okno, &pID);
				if (pID != 0)
				{
					uchwyt = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
					baza= dwGetModuleBaseAddress(pID, _T("Gothic2.exe"));  // nazwa procesu
					
					if (uchwyt == INVALID_HANDLE_VALUE || uchwyt == NULL || baza == NULL)
					{
						stanGry = "Niemam uchwytu.";
					}
					else
					{
						stanGry = "OK" ;
						jestGra = true;
					}
				}
				else 
				{
					stanGry = "Niemoge uzyskac dostepu do procesu";
				}
			}
			else
			{
				stanGry = "Niema okna";
			}



			 // wypisuje UI
			if (rysowac || jestGra && clock() - czasOstatnieOdswiezenie > 1000) 
			{
				
				rysowac = false;
				czasOstatnieOdswiezenie = clock();
				iloscHp = czytajINT(uchwyt,baza,ofsetBaza,ofsetAktualneHP);
				napisEXP = czytajINT(uchwyt, baza, ofsetBaza, ofsetAktualnyExp);
				napisPN = czytajINT(uchwyt, baza, ofsetBaza, ofsetPunktyNauki);
				napisOchrona1 = czytajINT(uchwyt, baza, ofsetBaza, ofsetOchronaBron);
				napisOchrona2 = czytajINT(uchwyt, baza, ofsetBaza, ofsetOchronaPociski);
				napisOchrona3 = czytajINT(uchwyt, baza, ofsetBaza, ofsetOchronaMagia);
				napisOchrona4 = czytajINT(uchwyt, baza, ofsetBaza, ofsetOchronaSmoczyOgien);
				napisLuki = czytajINT(uchwyt, baza, ofsetBaza, ofsetLuki);
				napisKusze = czytajINT(uchwyt, baza, ofsetBaza, ofsetKusze);
				napisBronie1h = czytajINT(uchwyt, baza, ofsetBaza, ofsetBronie1H);
				napisBronie2h = czytajINT(uchwyt, baza, ofsetBaza, ofsetBronie2h);
				napisZ = czytajLokacje(uchwyt, ofsetBaza, baza, ofsetZ);
				napisX = czytajLokacje(uchwyt, ofsetBaza, baza,ofsetX);
				napisY = czytajLokacje(uchwyt, ofsetBaza, baza,ofsetY);
				napisPN = czytajINT(uchwyt, ofsetBaza, baza, ofsetPunktyNauki);
				
				system("cls");
			
				
				cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-" << endl << endl ;
				cout << "END konczy, F12 zamraza hp, F11 teleport " << endl << endl;
				cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-" << endl << endl;
				cout << "              Status: " << stanGry << endl << endl;
				cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-" << endl << endl;
				cout << "pozycja Z :      [ " << napisZ<< " ] " << endl;
				cout << "pozycja X :      [ " << napisX << " ] " << endl;
				cout << "pozycja Y :      [ " << napisY << " ] " << endl;
				cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-" << endl << endl;
				cout << "HP :             [ " << iloscHp << " ]      << F11     [ " << napisHp << " ]" << endl;
				cout << "Punkty EXP :     [ " << napisEXP << " ]         << 1" << endl;
				cout << "Punkty Nauki :   [ " << napisPN << " ]          << 2" << endl;
				cout << "Bronie 1H :      [ " << napisBronie1h << "% ]       << 3" << endl;
				cout << "Bronie 2H :      [ " << napisBronie2h << "% ]       << 4 " << endl;
				cout << "Luki :           [ " << napisLuki << "% ]       << 5 " << endl;
				cout << "Kusze :          [ " << napisKusze << "% ]       << 6 " << endl;
				cout << "Ochrona  Bronia :         [ " << napisOchrona1 << " ] << 7" << endl;
				cout << "Ochrona  Pociski :        [ " << napisOchrona2 << " ] << 8 " << endl;
				cout << "Ochrona  Magia :          [ " << napisOchrona3 << " ] << 9 " << endl;
				cout << "Ochrona  Smoczy Ogien :   [ " << napisOchrona4 << " ] << 0" << endl << endl;
				
				cout << zmienia << endl;
			
                                 

			}
				// po UI




			/* cin.getline(d, 256);
			/switch (d[256])
			{
			case 'a':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetAktualnyExp, zapis);
				break;
			case 'b':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetPunktyNauki, zapis);
				break;
			case 'c':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetBronie1H, zapis);
				break;
			case 'd':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetBronie2h, zapis);
				break;
			case 'e':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetLuki, zapis);
				break;
			case 'f':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetKusze, zapis);
				break;
			case 'g':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetOchronaBron, zapis);
				break;
			case 'h':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetOchronaPociski, zapis);
				break;
			case 'i':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetOchronaMagia, zapis);
				break;
			case 'j':
				cout << "Podaj nowa wartosc" << endl;
				cin >> zapis;
				zapisz(uchwyt, baza, ofsetBaza, ofsetOchronaSmoczyOgien, zapis);
				break;
			}



			*/

		
			// timer do zamrazania hp

			if (jestGra && hp)
						{
											
						zapisz(uchwyt, baza, ofsetBaza, ofsetMaxHP, 100420);
						zapisz(uchwyt, baza, ofsetBaza, ofsetAktualneHP, 100420);
	                    
						napisHp = "Zamrozone";
					}
			
			// po timerze do zamrazaniahp hp

			
			// timer do zmieniania napisuHp gdy nie zamraza
				if (!hp || !jestGra)
				{
					hp = false;
					napisHp = "Nieaktywne";
				}

				
			
				// po timerze

				//timer do zapisywania lokacji
				
				if (jestGra && nowaLokacja)
				{
					zmienia = "Przenioslem";
				nowaLokacja = !nowaLokacja;
				piszLokacje(uchwyt,baza,ofsetBaza,ofsetX,ofsetY,ofsetZ);

				}
				//po timerze
				



				//klawisze do uruchamiania funkcji

			if (jestGra)
			{
				if (GetAsyncKeyState(VK_F12))
				{
					hp = !hp;
					
				}

				if (GetAsyncKeyState(VK_F11))
				{
					nowaLokacja = !nowaLokacja;

				}
			}

			


		}



	}


	
	
}