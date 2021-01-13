/** @file */
/*
Projekt PK2 - Gra w statki
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "structs.h"

int main() {
	int m = 6;//ustalasz m i n (na razie tak, potem mo�e bardziej interaktywnie)
	int n = 3;

	int M = m + 1;	//tutaj �eby sobie troch� u�atwi� zrobi�em zmienne o 1 wi�ksze od m i n �eby nie pisa� za ka�dym razem m+1, n+1
	int N = n + 1;

	FILE* slownik;
	if ((slownik = fopen("slownik.txt", "r")) == NULL) { //sprawdzamy czy istnieje plik slownik.txt
		printf("Nie moge otworzyc pliku!\n");
		exit(1);
	}

	char slowo[] = "";	//zmienne slowo i koniec do zapisywania tymczasowych sl�w z alfabetu
	char koniec[] = "";

	fpos_t pozycja = 0;	//zmienna do zapisanie pozycji pliku aby wr�ci� do miejsca gdzie sko�czyli�my (pobieranie kolejnego s�owa z kolejki)

	while (fscanf(slownik, "%s", slowo)) {	//pobieranie kolejnego s�owa z kolejki s�ownika
		printf("%s \n", slowo); //tymczasowe wy�wietlanie

		if (strlen(slowo) == m) {	//je�eli s�owo mniejsze ni� m to nie bierzemy pod uwag�
			fgetpos(slownik, &pozycja);	//zapisywanie pozycji w kt�rej sko�czyli�my, aby nie zaczyna� poeniera� s��w z pocz�tku s�ownika (np. sko�czyli�my na arbuz wi�c zaczniemy na kolejnym a nie 5 s��w dalej)
			rewind(slownik);	//powr�t do pocz�tku pliku aby m�c por�wna� s�owo (jego ko�c�wk�) ze wszystkimi s�owami ze s�ownika
			int a = 0;	//zmienna warunkowa, kt�ra okre�la czy ko�c�wka s�owa wyst�pi�a w s�owniku
			do {
				fscanf(slownik, "%s", koniec);	//pobranie kolejnej ko�c�wki do por�wnania ze s�owem
				if (feof(slownik) != 0) break;	//sprawdzenia czy nie wyst�pi� koniec pliku (czy sprawdzili�my wszystkie ko�c�wki)
				for (int i = n; i < M; i++) {
					if (slowo[i] != koniec[i - n])break;	//sprawdzenie n ostatnicz liter s�owa w ko�c�wce (czyli czy powinni�my wykluczy� s�owo i go nie wypisa�)
					a++;	//je�eli kolejne litery si� zgadzaj� to a++
				}
				if (a == N)break;	//je�eli ko�c�wka zgadza si� z ko�c�wk� s�owa to wykluczamy to s�owo i przerywamy p�tle while
			} while ((slowo[n] >= koniec[0]));	//je�eli natrafimy na liter� o wi�kszej warto�ci (ASCI) to nie ma sensu sprawdza� reszty np. pierwsza litera s�owa to a a wi�c bez sensu sprawdza� ko�c�wki zaczynaj�ce si� od b w g�r� (plik posortowany alfabetycznie)
			if (a != N) {	//tutaj warunek je�li nie znaleziono warunku wykluczaj�cego s�owa �eby go wypisa� jako rozwi�zanie
				printf("Siema");	//tymczasowe
				//je�eli nie znalaz� s�owa od przodu to powinnien szuka� tego od ty�u(jeszcze nie napisane)
			}
			fsetpos(slownik, &pozycja);	//przywr�cenie pozycji pliku przed sprawdzniem ko�c�wki �eby pobiera� s�owo kolejne z kolei a nie to na kt�rym sko�czyli�my sprawdzanie ko�c�wki s�owa w tym przypadku
			a = 0;	//wyzerowanie zmiennej warunkowej
		}
	}

	//printf("%s \n", koniec);

	//free(koniec);
	free(slowo);

	/*char* tabS = malloc(sizeof(char));
	char slowo[] = { "bakata" };
	tabS = slowo;
	printf("%s", tabS);*/

	fclose(slownik);

	return 0;
}